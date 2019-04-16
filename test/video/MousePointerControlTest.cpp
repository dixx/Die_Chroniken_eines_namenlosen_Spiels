#include "../../source/Leviathan/video/MousePointerControl.h"
#include "../../source/Leviathan/input/IEventProducer.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "../helpers/CatchPatches.hpp"
#include "../helpers/FakeitPatches.hpp"
#include "../helpers/Testhelper.h"
#include "../helpers/VideoDriverMock.hpp"
#include "irrlicht.h"

using namespace fakeit;

TEST_CASE("MousePointerControl", "[unit]") {
    Testhelper testhelper;
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe));
    Mock<irr::IrrlichtDevice> graphicDeviceMock;
    mocks::VideoDriverMock videoDriverMock;
    Mock<irr::video::ITexture> textureMock;
    Mock<irr::gui::ICursorControl> cursorControlMock;
    Fake(OverloadedMethod(cursorControlMock, setVisible, void(bool)));
    Mock<mocks::VideoDriverMock> videoDriverSpy(videoDriverMock);
    When(OverloadedMethod(videoDriverSpy, getTexture, irr::video::ITexture*(const irr::io::path&)))
        .AlwaysReturn(&textureMock.get());
    When(Method(graphicDeviceMock, getVideoDriver)).AlwaysReturn(&videoDriverMock);
    When(Method(graphicDeviceMock, getCursorControl)).AlwaysReturn(&cursorControlMock.get());
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
    leviathan::video::MousePointerControl subject(eventBrokerMock.get(), &graphicDeviceMock.get(), Testhelper::Logger());

    SECTION("events") {
        SECTION("subscribes to an event producer for movement input events") {
            // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
            Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
        }

        SECTION("does only handle mouse movement events") {
            REQUIRE_FALSE(subject.onEvent(keyboardEvent));
            REQUIRE_FALSE(subject.onEvent(mouseButtonEvent));
            REQUIRE(subject.onEvent(mouseMovementEvent));
        }

        SECTION("gets updated when the mouse is moved") {
            subject.createMousePointer(1, "test.png", irr::core::recti(0, 0, 40, 40), irr::core::vector2di(0, 0));
            subject.setActiveMousPointer(1);
            subject.draw();
            REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(0, 0));
            REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);

            videoDriverMock.ClearInvocationHistory();
            subject.onEvent(mouseMovementEvent);
            subject.draw();
            REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(123, 234));
            REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);
        }
    }

    SECTION("creation") {
        SECTION("can create a mouse pointer from image") {
            subject.createMousePointer(1, "test.png", irr::core::recti(0, 0, 40, 40), irr::core::vector2di(20, 20));

            SECTION("but will not overwrite an existing mouse pointer") {
                subject.createMousePointer(
                    1, "test2.png", irr::core::recti(40, 40, 80, 80), irr::core::vector2di(10, 10));
                subject.setActiveMousPointer(1);
                subject.draw();
                REQUIRE(videoDriverMock.mImageArea == irr::core::recti(0, 0, 40, 40));
                REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(-20, -20));
                REQUIRE(videoDriverMock.mpTexture == &textureMock.get());
            }

            SECTION("and creates no mouse arrow on error") {
                When(OverloadedMethod(videoDriverSpy, getTexture, irr::video::ITexture*(const irr::io::path&)))
                    .Return(nullptr);
                subject.createMousePointer(
                    2, "unknown_image.png", irr::core::recti(0, 0, 40, 40), irr::core::vector2di(20, 20));
                subject.setActiveMousPointer(2);
                subject.draw();
                REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 0);
            }
        }
    }

    SECTION("display") {
        subject.createMousePointer(1, "test.png", irr::core::recti(40, 40, 80, 80), irr::core::vector2di(20, 20));
        subject.createMousePointer(2, "test.png", irr::core::recti(130, 130, 140, 140), irr::core::vector2di(2, 4));

        SECTION("draws the current mouse pointer") {
            subject.setActiveMousPointer(1);
            subject.draw();
            REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);
            REQUIRE(videoDriverMock.mpTexture == &textureMock.get());
            REQUIRE(videoDriverMock.mImageArea == irr::core::recti(40, 40, 80, 80));
            REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(-20, -20));
            REQUIRE(videoDriverMock.mClippingRectangle == nullptr);
            REQUIRE(videoDriverMock.mBackgroundColor == irr::video::SColor(255, 255, 255, 255));
            REQUIRE(videoDriverMock.mUseAlphaChannel == true);
        }

        SECTION("can switch between mouse pointers") {
            subject.setActiveMousPointer(2);
            subject.draw();
            REQUIRE(videoDriverMock.mImageArea == irr::core::recti(130, 130, 140, 140));
            REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(-2, -4));
        }

        SECTION("defaults to the system mouse arrow on unknown mouse pointer id") {
            subject.setActiveMousPointer(42);
            subject.draw();
            REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 0);
        }
    }
}
