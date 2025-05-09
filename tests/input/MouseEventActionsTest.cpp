#include "../../src/Leviathan/input/MouseEventActions.h"
#include "../helpers/CatchPatches.hpp"
#include "catch.hpp"
#include <cstdint>
#include <input/Action.h>
#include <vector>

TEST_CASE("Mouse events to actions converter", "[unit]") {
    irr::SEvent event;
    event.EventType = irr::EET_MOUSE_INPUT_EVENT;
    event.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
    event.MouseInput.ButtonStates = irr::EMBSM_LEFT | irr::EMBSM_RIGHT;
    leviathan::input::MouseEventActions subject = leviathan::input::MouseEventActions();

    SECTION("#addMapping stores action ids per event id") {
        std::vector<leviathan::input::Action> expectedActions({{1, true}, {2, true}, {4, true}});
        subject.addMapping(irr::EMBSM_LEFT, 1);
        subject.addMapping(irr::EMBSM_LEFT, 2);
        subject.addMapping(irr::EMBSM_LEFT, 4);

        CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
        CHECK_THAT(subject.actionsFor(event)[1], ActionEqual(expectedActions[1]));
        CHECK_THAT(subject.actionsFor(event)[2], ActionEqual(expectedActions[2]));

        SECTION("and keeps the list unique") {
            subject.addMapping(irr::EMBSM_LEFT, 2);
            CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            CHECK_THAT(subject.actionsFor(event)[1], ActionEqual(expectedActions[1]));
            CHECK_THAT(subject.actionsFor(event)[2], ActionEqual(expectedActions[2]));
        }
    }

    SECTION("#clear empties all actions") {
        subject.addMapping(irr::EMBSM_LEFT, 1);
        subject.clear();
        REQUIRE(subject.actionsFor(event).empty());
    }

    SECTION("#actionsFor") {
        SECTION("returns an empty list for unknown mouse events") {
            REQUIRE(subject.actionsFor(event).empty());
        }

        SECTION("returns appropriate list of actions for any given mouse button event") {
            subject.addMapping(irr::EMBSM_LEFT, 1);
            subject.addMapping(irr::EMBSM_MIDDLE, 2);
            subject.addMapping(irr::EMBSM_RIGHT, 4);

            SECTION("left mouse button pressed down") {
                std::vector<leviathan::input::Action> expectedActions({{1, true}});
                event.MouseInput.Event = irr::EMIE_LMOUSE_PRESSED_DOWN;
                event.MouseInput.ButtonStates = irr::EMBSM_LEFT;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("middle mouse button pressed down") {
                std::vector<leviathan::input::Action> expectedActions({{2, true}});
                event.MouseInput.Event = irr::EMIE_MMOUSE_PRESSED_DOWN;
                event.MouseInput.ButtonStates = irr::EMBSM_MIDDLE;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("right mouse button pressed down") {
                std::vector<leviathan::input::Action> expectedActions({{4, true}});
                event.MouseInput.Event = irr::EMIE_RMOUSE_PRESSED_DOWN;
                event.MouseInput.ButtonStates = irr::EMBSM_RIGHT;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("left mouse button left up") {
                std::vector<leviathan::input::Action> expectedActions({{1, false}});
                event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
                event.MouseInput.ButtonStates = 0;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("middle mouse button left up") {
                std::vector<leviathan::input::Action> expectedActions({{2, false}});
                event.MouseInput.Event = irr::EMIE_MMOUSE_LEFT_UP;
                event.MouseInput.ButtonStates = 0;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("right mouse button left up") {
                std::vector<leviathan::input::Action> expectedActions({{4, false}});
                event.MouseInput.Event = irr::EMIE_RMOUSE_LEFT_UP;
                event.MouseInput.ButtonStates = 0;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("can handle multistate mouse events") {
                std::vector<leviathan::input::Action> expectedActions({{1, false}});
                event.MouseInput.Event = irr::EMIE_LMOUSE_LEFT_UP;
                event.MouseInput.ButtonStates = irr::EMBSM_MIDDLE | irr::EMBSM_RIGHT;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }
        }
    }
}
