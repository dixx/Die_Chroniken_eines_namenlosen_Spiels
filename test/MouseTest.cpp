#include <catch.hpp>
#include "leviathan.h"

TEST_CASE("Mouse") {
    leviathan::input::Mouse subject;

    SECTION("default values") {
        REQUIRE_FALSE(subject.isLMBDown());
        REQUIRE_FALSE(subject.isMMBDown());
        REQUIRE_FALSE(subject.isRMBDown());
        REQUIRE_FALSE(subject.wasLMBDown());
        REQUIRE_FALSE(subject.wasMMBDown());
        REQUIRE_FALSE(subject.wasRMBDown());
        REQUIRE_FALSE(subject.isWheelMovedUp());
        REQUIRE_FALSE(subject.isWheelMovedDown());
        REQUIRE(subject.getPosition() == irr::core::position2di(0, 0));
        REQUIRE(subject.getLastPosition() == irr::core::position2di(0, 0));
        REQUIRE(subject.getWheelDelta() == Approx(0.0f));
    }

    SECTION("buttons and coordinates are set asynchronous by an event receiver") {
        subject.setButtonState(leviathan::input::Mouse::Button::LEFT, true);
        subject.setCoordinates(10, 20);
        subject.setWheelDelta(30.0f);
        REQUIRE(subject.isLMBDown());
        REQUIRE_FALSE(subject.isMMBDown());
        REQUIRE(subject.getPosition() == irr::core::position2di(10, 20));
        REQUIRE(subject.getWheelDelta() == Approx(30.0f));
        subject.setButtonState(leviathan::input::Mouse::Button::LEFT, false);
        subject.setButtonState(leviathan::input::Mouse::Button::MIDDLE, true);
        subject.setCoordinates(30, 10);
        subject.setWheelDelta(-2.2f);
        REQUIRE_FALSE(subject.isLMBDown());
        REQUIRE(subject.isMMBDown());
        REQUIRE(subject.getPosition() == irr::core::position2di(30, 10));
        REQUIRE_FALSE(subject.isWheelMovedUp());
        REQUIRE(subject.isWheelMovedDown());
        REQUIRE(subject.getWheelDelta() == Approx(-2.2f));
    }

    SECTION("button states and coordinates create history on update") {
        subject.setButtonState(leviathan::input::Mouse::Button::RIGHT, true);
        subject.setCoordinates(11, 22);
        subject.setWheelDelta(33.3f);
        REQUIRE(subject.isRMBDown());
        REQUIRE(subject.getPosition() == irr::core::position2di(11, 22));
        REQUIRE(subject.isWheelMovedUp());
        REQUIRE(subject.getWheelDelta() == Approx(33.3f));
        subject.update();
        subject.setButtonState(leviathan::input::Mouse::Button::RIGHT, false);
        subject.setCoordinates(111, 222);
        subject.setWheelDelta(-6.9f);
        REQUIRE_FALSE(subject.isRMBDown());
        REQUIRE(subject.wasRMBDown());
        REQUIRE(subject.getPosition() == irr::core::position2di(111, 222));
        REQUIRE(subject.getLastPosition() == irr::core::position2di(11, 22));
        REQUIRE(subject.isWheelMovedDown());
        REQUIRE(subject.getWheelDelta() == Approx(-6.9f));

        SECTION("key states are cleared without continuous input") {
            subject.update();
            REQUIRE(subject.getLastPosition() == irr::core::position2di(111, 222));

            SECTION("...but mousewheel is updated by events only") {
                REQUIRE(subject.getWheelDelta() == Approx(-6.9f)); // TODO check why this is inconsistent with the rest
            }
        }
    }
}
