#include "../../source/Leviathan/video/MousePointerControl.h"
#include "../../source/Leviathan/input/IEventProducer.h"
#include "catch.hpp"
#include "fakeit.hpp"
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
    When(Method(graphicDeviceMock, getVideoDriver)).AlwaysReturn(&videoDriverMock);
    irr::SEvent mouseMovementEvent, mouseButtonEvent;
    mouseButtonEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    mouseButtonEvent.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
    mouseButtonEvent.MouseInput.X = 45;
    mouseButtonEvent.MouseInput.Y = 67;
    mouseMovementEvent.EventType = irr::EET_MOUSE_INPUT_EVENT;
    mouseMovementEvent.MouseInput.Event = irr::EMIE_MOUSE_MOVED;
    mouseMovementEvent.MouseInput.X = 123;
    mouseMovementEvent.MouseInput.Y = 234;
    leviathan::video::MousePointerControl subject(eventBrokerMock.get(), &graphicDeviceMock.get());

    SECTION("subscribes to an event producer for movement input events") {
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
    }

    SECTION("does only handle mouse movement events") {
        REQUIRE_FALSE(subject.onEvent(mouseButtonEvent));
        REQUIRE(subject.onEvent(mouseMovementEvent));
    }

    SECTION("gets updated when the mouse is moved") {
        subject.draw();
        REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(0, 0));
        REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);
        videoDriverMock.ClearInvocationHistory();

        subject.onEvent(mouseMovementEvent);
        subject.draw();
        REQUIRE(videoDriverMock.mPosition == irr::core::vector2di(123, 234));
        REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);
    }

    SECTION("can create a mouse pointer from image") {
        subject.createMousePointer(
            1, "test_image.png", irr::core::recti(0, 0, 40, 40), irr::core::vector2di(20, 20));
        subject.setActiveMousPointer(1);
        REQUIRE(true);

        SECTION("and creates a system mouse arrow on error") {
            subject.createMousePointer(
                2, "unknown_image.png", irr::core::recti(0, 0, 40, 40), irr::core::vector2di(20, 20));
            subject.setActiveMousPointer(2);
            REQUIRE(true);
        }

        SECTION("but will overwrite an existing mouse pointer") {
            subject.createMousePointer(
            1, "test_image.png", irr::core::recti(40, 40, 80, 80), irr::core::vector2di(20, 20));
            subject.setActiveMousPointer(1);
            REQUIRE(true);
        }
    }

    SECTION("draws the current mouse pointer") {
        subject.setActiveMousPointer(1);
        subject.draw();
        REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);
        videoDriverMock.ClearInvocationHistory();

        subject.setActiveMousPointer(2);
        subject.draw();
        REQUIRE(videoDriverMock.mDraw2DImageArgsCallCount == 1);
        videoDriverMock.ClearInvocationHistory();

        SECTION("always fully opaque with transparent parts") {
            subject.draw();
            REQUIRE(videoDriverMock.mClippingRectangle == nullptr);
            REQUIRE(videoDriverMock.mBackgroundColor == irr::video::SColor(255, 255, 255, 255));
            REQUIRE(videoDriverMock.mUseAlphaChannel == true);
        }
    }

    SECTION("can change mouse pointer visibility") {}
}
