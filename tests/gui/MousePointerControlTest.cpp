#include "../../src/Leviathan/gui/MousePointerControl.h"
#include "../../src/Leviathan/core/Configuration.h"
#include "../../src/Leviathan/input/IEventProducer.h"
#include "../../src/Leviathan/video/Constants.h"
#include "../../src/Leviathan/video/GraphicEngine.h"
#include "../../src/Leviathan/video/Textures.h"
#include "../helpers/CatchPatches.hpp"
#include "../helpers/FakeitPatches.hpp"
#include "../helpers/TestHelper.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <gui/MousePointerConfiguration.h>

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)
#define draw2DImageArgs \
    void(const irr::video::ITexture*, const irr::core::vector2di&, const irr::core::recti&, const irr::core::recti*, \
        irr::video::SColor, bool)
#define makeColorKeyTextureArgs void(irr::video::ITexture*, irr::video::SColor, bool)

TEST_CASE("MousePointerControl", "[unit]") {
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe));
    Mock<irr::video::ITexture> textureMock;
    Mock<irr::video::IVideoDriver> videoDriverMock;
    When(OverloadedMethod(videoDriverMock, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
    leviathan::video::Textures textures(&videoDriverMock.get(), TestHelper::Logger());
    // FakeIt has a bug (https://github.com/eranpeer/FakeIt/issues/92) where reference arguments are tested way too
    // late, so we have to remember them at call time:
    irr::core::vector2di lastRememberedPosition;
    irr::core::recti lastRememberedImageArea;
    When(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs))
        .AlwaysDo([&](const irr::video::ITexture* a, const irr::core::vector2di& position,
                      const irr::core::recti& imageArea, const irr::core::recti* d, irr::video::SColor e, bool f) {
            (void)a;
            (void)d;
            (void)e;
            (void)f;
            lastRememberedPosition = position;
            lastRememberedImageArea = imageArea;
        });
    Fake(ConstOverloadedMethod(videoDriverMock, makeColorKeyTexture, makeColorKeyTextureArgs));
    Fake(Method(videoDriverMock, setTextureCreationFlag));
    Mock<irr::IrrlichtDevice> graphicEngineMock;
    When(Method(graphicEngineMock, getVideoDriver)).AlwaysReturn(&videoDriverMock.get());
    Mock<irr::gui::ICursorControl> cursorControlMock;
    Fake(Method(cursorControlMock, setVisible));
    When(Method(graphicEngineMock, getCursorControl)).AlwaysReturn(&cursorControlMock.get());
    Fake(Method(graphicEngineMock, setEventReceiver), Method(graphicEngineMock, closeDevice));
    Mock<irr::IEventReceiver> eventReceiverMock;
    leviathan::core::Configuration config("idontcare");
    leviathan::video::GraphicEngine::overrideGraphicEngine(&graphicEngineMock.get());
    leviathan::video::GraphicEngine graphicEngine(eventReceiverMock.get(), TestHelper::Logger(), config);
    irr::SEvent mouseMovementEvent, mouseButtonEvent, keyboardEvent;
    mouseButtonEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    mouseButtonEvent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
    mouseButtonEvent.MouseInput.X = 45;
    mouseButtonEvent.MouseInput.Y = 67;
    mouseMovementEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    mouseMovementEvent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
    mouseMovementEvent.MouseInput.X = 123;
    mouseMovementEvent.MouseInput.Y = 234;
    keyboardEvent.EventType = irr::EET_KEY_INPUT_EVENT;
    keyboardEvent.KeyInput.Key = irr::KEY_RETURN;
    keyboardEvent.KeyInput.PressedDown = true;

    leviathan::gui::MousePointerControl subject(eventBrokerMock.get(), graphicEngine, TestHelper::Logger(), textures);

    SECTION("events") {
        SECTION("subscribes to an event producer for movement input events") {
            // FIXME: issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
            Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
            VerifyNoOtherInvocations(eventBrokerMock);
        }

        SECTION("does only handle mouse movement events") {
            REQUIRE_FALSE(subject.onEvent(keyboardEvent));
            REQUIRE_FALSE(subject.onEvent(mouseButtonEvent));
            REQUIRE(subject.onEvent(mouseMovementEvent));
        }

        SECTION("gets updated when the mouse is moved") {
            videoDriverMock.ClearInvocationHistory();

            subject.addMousePointer(1, {"test.png", {{0, 0}, {40, 40}}, {0, 0}});
            subject.setActiveMousPointer(1);
            subject.draw();
            Verify(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs)
                       .Using(&textureMock.get(), _, _, _, _, _))
                .Exactly(Once);
            REQUIRE(lastRememberedPosition == irr::core::vector2di(0, 0));

            videoDriverMock.ClearInvocationHistory();
            subject.onEvent(mouseMovementEvent);
            subject.draw();
            Verify(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs)
                       .Using(&textureMock.get(), _, _, _, _, _))
                .Exactly(Once);
            REQUIRE(lastRememberedPosition == irr::core::vector2di(123, 234));
        }
    }

    SECTION("creation") {
        SECTION("can create a mouse pointer from image") {
            subject.addMousePointer(1, {"test.png", {{0, 0}, {40, 40}}, {20, 20}});

            SECTION("with color key transparency") {
                Verify(ConstOverloadedMethod(videoDriverMock, makeColorKeyTexture, makeColorKeyTextureArgs)
                           .Using(&textureMock.get(), leviathan::video::COL_MAGICPINK, false))
                    .Once();
            }

            SECTION("but will not overwrite an existing mouse pointer") {
                videoDriverMock.ClearInvocationHistory();
                subject.addMousePointer(1, {"test2.png", {{40, 40}, {80, 80}}, {10, 10}});
                subject.setActiveMousPointer(1);
                subject.draw();
                Verify(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs)
                           .Using(&textureMock.get(), _, _, _, _, _))
                    .Exactly(Once);
                REQUIRE(lastRememberedPosition == irr::core::vector2di(-20, -20));
                REQUIRE(lastRememberedImageArea == irr::core::recti(0, 0, 40, 40));
            }

            SECTION("and creates no mouse arrow on error") {
                videoDriverMock.ClearInvocationHistory();
                When(OverloadedMethod(videoDriverMock, getTexture, getTextureArgs)).Return(nullptr);
                subject.addMousePointer(2, {"unknown_image.png", {{0, 0}, {40, 40}}, {20, 20}});
                subject.setActiveMousPointer(2);
                subject.draw();
                VerifyNoOtherInvocations(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs));
            }
        }
    }

    SECTION("display") {
        subject.addMousePointer(1, {"test.png", {{40, 40}, {80, 80}}, {20, 20}});
        subject.addMousePointer(2, {"test.png", {{130, 130}, {140, 140}}, {2, 4}});
        videoDriverMock.ClearInvocationHistory();

        SECTION("draws the current mouse pointer") {
            subject.setActiveMousPointer(1);
            subject.draw();
            Verify(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs)
                       .Using(&textureMock.get(), _, _, nullptr, irr::video::SColor(255, 255, 255, 255), true))
                .Exactly(Once);
            REQUIRE(lastRememberedPosition == irr::core::vector2di(-20, -20));
            REQUIRE(lastRememberedImageArea == irr::core::recti(40, 40, 80, 80));
        }

        SECTION("can switch between mouse pointers") {
            subject.setActiveMousPointer(2);
            subject.draw();
            Verify(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs)
                       .Using(&textureMock.get(), _, _, _, _, _))
                .Exactly(Once);
            REQUIRE(lastRememberedPosition == irr::core::vector2di(-2, -4));
            REQUIRE(lastRememberedImageArea == irr::core::recti(130, 130, 140, 140));
        }

        SECTION("defaults to the system mouse arrow on unknown mouse pointer id") {
            subject.setActiveMousPointer(42);
            subject.draw();
            VerifyNoOtherInvocations(OverloadedMethod(videoDriverMock, draw2DImage, draw2DImageArgs));
        }
    }
}
