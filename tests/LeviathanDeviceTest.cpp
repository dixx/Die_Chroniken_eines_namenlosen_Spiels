#include "../src/Leviathan/LeviathanDevice.h"
#include "IGUIEnvironment.h"
#include "IMeshCache.h"
#include "ISceneCollisionManager.h"
#include "ISceneManager.h"
#include "ITimer.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "helpers/TestHelper.h"
#include <cstdint>
#include <typeinfo>

using namespace fakeit;

TEST_CASE("LeviathanDevice supporter", "[integration]") {
    const char* configFileName = "testconfigfile.yaml";
    TestHelper::writeFile(configFileName, "---\nvideo:\n  max_fps: 100\n  driver: \"NULL\"\n");
    leviathan::LeviathanDevice subject(configFileName);

    SECTION("it provides instances of usefull tools") {
        REQUIRE(typeid(subject.Actions()) == typeid(leviathan::input::Actions));
        REQUIRE(&subject.Actions() != nullptr);
        REQUIRE(typeid(subject.Configuration()) == typeid(leviathan::core::Configuration));
        REQUIRE(&subject.Configuration() != nullptr);
        REQUIRE(typeid(subject.EventReceiver()) == typeid(leviathan::input::EventReceiver));
        REQUIRE(&subject.EventReceiver() != nullptr);
        REQUIRE(typeid(subject.GameStateManager()) == typeid(leviathan::core::GameStateManager));
        REQUIRE(&subject.GameStateManager() != nullptr);
        REQUIRE(typeid(subject.Logger()) == typeid(leviathan::core::Logger));
        REQUIRE(&subject.Logger() != nullptr);
        REQUIRE(typeid(subject.MenuControl()) == typeid(leviathan::gui::MenuControl));
        REQUIRE(&subject.MenuControl() != nullptr);
        REQUIRE(typeid(subject.MousePointerControl()) == typeid(leviathan::gui::MousePointerControl));
        REQUIRE(&subject.MousePointerControl() != nullptr);
        REQUIRE(typeid(subject.Camera()) == typeid(leviathan::video::Camera));
        REQUIRE(&subject.Camera() != nullptr);
        REQUIRE(typeid(subject.Randomizer()) == typeid(leviathan::core::Randomizer));
        REQUIRE(&subject.Randomizer() != nullptr);
        REQUIRE(typeid(subject.TimeControl()) == typeid(leviathan::core::TimeControl));
        REQUIRE(&subject.TimeControl() != nullptr);
        REQUIRE(typeid(subject.Heroes()) == typeid(leviathan::characters::Heroes));
        REQUIRE(&subject.Heroes() != nullptr);
        REQUIRE(typeid(subject.Collider()) == typeid(leviathan::world::Collider));
        REQUIRE(&subject.Collider() != nullptr);
        REQUIRE(typeid(subject.Ground()) == typeid(leviathan::world::Ground));
        REQUIRE(&subject.Ground() != nullptr);
    }
}

TEST_CASE("LeviathanDevice main loop", "[unit]") {
    Mock<irr::ITimer> timerMock;
    When(Method(timerMock, getTime)).AlwaysReturn(0);
    Mock<irr::IrrlichtDevice> graphicEngineMock;
    Mock<irr::video::IVideoDriver> videoDriverMock;
    Mock<irr::scene::ISceneManager> sceneManagerMock;
    Mock<irr::scene::ISceneCollisionManager> collisionManagerMock;
    Mock<irr::gui::IGUIEnvironment> guiEnvironmentMock;
    Mock<irr::scene::IMeshCache> meshCacheMock;
    irr::scene::ICameraSceneNode* cameraDummy = TestHelper::graphicEngine()->getSceneManager()->addCameraSceneNode();
    irr::scene::ISceneNode* nodeDummy = TestHelper::graphicEngine()->getSceneManager()->addEmptySceneNode();
    Fake(Method(videoDriverMock, beginScene), Method(videoDriverMock, endScene));
    Fake(Method(meshCacheMock, clearUnusedMeshes));
    Fake(Method(sceneManagerMock, drawAll));
    When(Method(sceneManagerMock, getMeshCache)).AlwaysReturn(&meshCacheMock.get());
    When(Method(sceneManagerMock, getSceneCollisionManager)).AlwaysReturn(&collisionManagerMock.get());
    When(Method(sceneManagerMock, addCameraSceneNode)).AlwaysReturn(cameraDummy);
    When(Method(sceneManagerMock, addEmptySceneNode)).AlwaysReturn(nodeDummy);
    Fake(Method(guiEnvironmentMock, addEmptySpriteBank));
    When(Method(graphicEngineMock, getVideoDriver)).AlwaysReturn(&videoDriverMock.get());
    When(Method(graphicEngineMock, getSceneManager)).AlwaysReturn(&sceneManagerMock.get());
    When(Method(graphicEngineMock, getGUIEnvironment)).AlwaysReturn(&guiEnvironmentMock.get());
    When(Method(graphicEngineMock, getTimer)).AlwaysReturn(&timerMock.get());
    When(Method(graphicEngineMock, isWindowActive)).AlwaysReturn(true);
    Fake(Method(graphicEngineMock, yield), Method(graphicEngineMock, setEventReceiver),
        Method(graphicEngineMock, closeDevice));
    leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
    const char* configFileName = "testconfigfile.yaml";
    TestHelper::writeFile(configFileName, "---\nvideo:\n  max_fps: 100\n  driver: \"NULL\"\n");
    leviathan::LeviathanDevice subject(configFileName);
    Mock<leviathan::core::IGameState> gameStateMock;
    Fake(Method(gameStateMock, update), Method(gameStateMock, draw), Method(gameStateMock, setActive),
        Method(gameStateMock, setInactive));
    subject.GameStateManager().add(gameStateMock.get(), 42);
    subject.GameStateManager().transitTo(42);

    SECTION("it can be halted") {
        subject.halt();
        Verify(Method(graphicEngineMock, closeDevice)).Exactly(1_Times);
    }

    SECTION("it should be fair to other apps if inactive") {
        When(Method(graphicEngineMock, run)).Return(5_Times(true), false);
        When(Method(graphicEngineMock, isWindowActive)).Return(true, true, false, false, true);
        subject.run();
        Verify(Method(graphicEngineMock, yield)).Exactly(2_Times);
    }

    SECTION("it should not draw if engine is shut down directly after game state update") {
        When(Method(graphicEngineMock, run)).Return(true, false);
        subject.run();
        Verify(Method(gameStateMock, draw)).Exactly(0_Times);
    }

    SECTION("performance tests") {
        uint32_t virtualTime = 0;
        When(Method(timerMock, getTime)).AlwaysDo([&virtualTime] { return virtualTime++; });
        When(Method(graphicEngineMock, run)).AlwaysDo([&virtualTime] { return virtualTime < 1000; });

        SECTION("without calculation stress") {
            subject.run();
            SECTION("it should draw with a fixed maximum frame rate") {
                Verify(Method(gameStateMock, draw)).Exactly(100_Times);
                SECTION("and it should update every cycle") {
                    Verify(Method(gameStateMock, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with peak load") {
            When(Method(gameStateMock, draw)).AlwaysDo([&virtualTime] {
                if (virtualTime == 3) virtualTime += 800;
            });
            When(Method(gameStateMock, update)).AlwaysDo([&virtualTime](...) { virtualTime++; });
            subject.run();
            SECTION("it should draw with a fixed maximum frame rate") {
                Verify(Method(gameStateMock, draw)).Exactly(100_Times);
                SECTION("and it should update every cycle") {
                    Verify(Method(gameStateMock, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with sometimes zero elapsed time") {
            std::srand(42);
            When(Method(timerMock, getTime)).AlwaysDo([&virtualTime] {
                return (std::rand() & 1) ? virtualTime : virtualTime++;
            });
            subject.run();
            SECTION("it should draw with a fixed maximum frame rate") {
                Verify(Method(gameStateMock, draw)).Exactly(100_Times);
                SECTION("and it should update every cycle") {
                    Verify(Method(gameStateMock, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with moderate calculation stress") {
            When(Method(gameStateMock, draw)).AlwaysDo([&virtualTime] { virtualTime += 8; });
            When(Method(gameStateMock, update)).AlwaysDo([&virtualTime](...) { virtualTime++; });
            subject.run();
            SECTION("it should begin to skip frames") {
                Verify(Method(gameStateMock, draw)).AtLeast(85_Times);
                SECTION("but it should update every cycle") {
                    Verify(Method(gameStateMock, update)).Exactly(100_Times);
                }
            }
        }

        SECTION("with much calculation stress") {
            When(Method(gameStateMock, draw)).AlwaysDo([&virtualTime] { virtualTime += 200; });
            When(Method(gameStateMock, update)).AlwaysDo([&virtualTime](...) { virtualTime++; });
            subject.run();
            SECTION("it should still try to draw") {
                Verify(Method(gameStateMock, draw)).AtLeast(5_Times);
                SECTION("and it should try to update many cycles") {
                    Verify(Method(gameStateMock, update)).AtLeast(40_Times);
                }
            }
        }
    }
}
