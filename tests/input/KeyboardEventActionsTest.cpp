#include "../../src/Leviathan/input/KeyboardEventActions.h"
#include "../helpers/CatchPatches.hpp"
#include "catch.hpp"
#include <cstdint>
#include <input/Action.h>
#include <vector>

TEST_CASE("Keyboard events to actions converter", "[unit]") {
    irr::SEvent event;
    event.EventType = irr::EET_KEY_INPUT_EVENT;
    event.KeyInput.Key = irr::KEY_SPACE;
    event.KeyInput.PressedDown = true;
    leviathan::input::KeyboardEventActions subject = leviathan::input::KeyboardEventActions();

    SECTION("#addMapping stores action ids per event id") {
        std::vector<leviathan::input::Action> expectedActions({{1, true}, {2, true}, {4, true}});
        subject.addMapping(irr::KEY_SPACE, 1);
        subject.addMapping(irr::KEY_SPACE, 2);
        subject.addMapping(irr::KEY_SPACE, 4);

        CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
        CHECK_THAT(subject.actionsFor(event)[1], ActionEqual(expectedActions[1]));
        CHECK_THAT(subject.actionsFor(event)[2], ActionEqual(expectedActions[2]));

        SECTION("and keeps the list unique") {
            subject.addMapping(irr::KEY_SPACE, 2);
            CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            CHECK_THAT(subject.actionsFor(event)[1], ActionEqual(expectedActions[1]));
            CHECK_THAT(subject.actionsFor(event)[2], ActionEqual(expectedActions[2]));
        }
    }

    SECTION("#clear empties all actions") {
        subject.addMapping(irr::KEY_SPACE, 1);
        subject.clear();
        REQUIRE(subject.actionsFor(event).empty());
    }

    SECTION("#actionsFor") {
        SECTION("returns an empty list for unknown keyboard events") {
            REQUIRE(subject.actionsFor(event).empty());
        }

        SECTION("returns appropriate list of actions for any given keyboard event") {
            subject.addMapping(irr::KEY_SPACE, 1);
            subject.addMapping(irr::KEY_KEY_E, 2);

            SECTION("SPACE pressed down") {
                std::vector<leviathan::input::Action> expectedActions({{1, true}});
                event.KeyInput.Key = irr::KEY_SPACE;
                event.KeyInput.PressedDown = true;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("E pressed down") {
                std::vector<leviathan::input::Action> expectedActions({{2, true}});
                event.KeyInput.Key = irr::KEY_KEY_E;
                event.KeyInput.PressedDown = true;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("left keyboard button left up") {
                std::vector<leviathan::input::Action> expectedActions({{1, false}});
                event.KeyInput.Key = irr::KEY_SPACE;
                event.KeyInput.PressedDown = false;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }

            SECTION("middle keyboard button left up") {
                std::vector<leviathan::input::Action> expectedActions({{2, false}});
                event.KeyInput.Key = irr::KEY_KEY_E;
                event.KeyInput.PressedDown = false;
                CHECK_THAT(subject.actionsFor(event)[0], ActionEqual(expectedActions[0]));
            }
        }
    }
}
