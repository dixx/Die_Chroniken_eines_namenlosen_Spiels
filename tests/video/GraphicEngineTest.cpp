#include "../../src/Leviathan/video/GraphicEngine.h"
#include "../../src/Leviathan/core/Configuration.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"
#include <typeinfo>

using namespace fakeit;

TEST_CASE("GraphicEngine", "[integration]") {
    Mock<irr::IEventReceiver> eventReceiverMock;
    Fake(Method(eventReceiverMock, OnEvent));
    const char* configFileName = "testconfigfile.yaml";
    TestHelper::writeFile(configFileName, "---\nvideo:\n  driver: \"NULL\"\n  screen_x: 1\n  screen_y: 2\n");
    leviathan::core::Configuration config(configFileName);
    leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);

    SECTION("initialize with configuration") {
        REQUIRE(subject.getVideoDriver()->getDriverType() == irr::video::EDT_NULL);
        REQUIRE(subject.getVideoDriver()->getScreenSize().Width == 1);
        REQUIRE(subject.getVideoDriver()->getScreenSize().Height == 2);
    }

    SECTION("it provides instances to internal manager objects") {
        REQUIRE(typeid(subject.getCursorControl()) == typeid(irr::gui::ICursorControl*));
        REQUIRE(subject.getCursorControl() != nullptr);
        REQUIRE(typeid(subject.getGUIEnvironment()) == typeid(irr::gui::IGUIEnvironment*));
        REQUIRE(subject.getGUIEnvironment() != nullptr);
        REQUIRE(typeid(subject.getSceneManager()) == typeid(irr::scene::ISceneManager*));
        REQUIRE(subject.getSceneManager() != nullptr);
        REQUIRE(typeid(subject.getVideoDriver()) == typeid(irr::video::IVideoDriver*));
        REQUIRE(subject.getVideoDriver() != nullptr);
    }

    SECTION("gracefully shuts down graphic engine") {
        REQUIRE(subject.run());
        subject.closeDevice();
        REQUIRE_FALSE(subject.run());
    }
}

TEST_CASE("GraphicEngine override", "[integration]") {
    Mock<irr::IEventReceiver> eventReceiverMock;
    Fake(Method(eventReceiverMock, OnEvent));
    Mock<irr::IrrlichtDevice> graphicEngineMock;
    Fake(Method(graphicEngineMock, run), Method(graphicEngineMock, setEventReceiver),
        Method(graphicEngineMock, closeDevice));
    const char* configFileName = "testconfigfile.yaml";
    TestHelper::writeFile(configFileName, "---\nvideo:\n  driver: \"NULL\"\n  screen_x: 1\n  screen_y: 2\n");
    leviathan::core::Configuration config(configFileName);

    SECTION("cannot instantiate an internal engine after override") {
        leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
        leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);
        subject.closeDevice();
        Verify(Method(graphicEngineMock, closeDevice)).Exactly(Once);
    }

    SECTION("nullptr resets the override mode") {
        leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
        {
            leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);
            subject.run();
            Verify(Method(graphicEngineMock, run)).Exactly(Once);
        }
        leviathan::video::GraphicEngine::overrideGraphicEngine(nullptr);
        {
            leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);
            subject.run();
            VerifyNoOtherInvocations(Method(graphicEngineMock, run));
        }

        SECTION("cannot be reset if not overridden") {
            leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);
            REQUIRE(subject.run());
            leviathan::video::GraphicEngine::overrideGraphicEngine(nullptr);
            REQUIRE(subject.run());
        }
    }

    SECTION("cannot be overridden after instantiation of an internal engine") {
        leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);
        leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
        subject.closeDevice();
        VerifyNoOtherInvocations(Method(graphicEngineMock, closeDevice));
    }

    SECTION("cannot be overridden more than once in a row") {
        Mock<irr::IrrlichtDevice> anotherGraphicEngineMock;
        Fake(Method(anotherGraphicEngineMock, closeDevice));
        leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
        leviathan::video::GraphicEngine::overrideGraphicEngine(&anotherGraphicEngineMock.get());
        leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config);
        subject.closeDevice();
        Verify(Method(graphicEngineMock, closeDevice)).Exactly(Once);
        VerifyNoOtherInvocations(Method(anotherGraphicEngineMock, closeDevice));
    }

    SECTION("does not destroy overriding graphic engine") {
        Fake(Dtor(graphicEngineMock));
        leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
        { leviathan::video::GraphicEngine subject(eventReceiverMock.get(), TestHelper::Logger(), config); }
        VerifyNoOtherInvocations(Dtor(graphicEngineMock));
    }
}
