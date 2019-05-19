#include "../../source/Leviathan/gui/MenuControl.h"
#include "../../source/Leviathan/input/IEventProducer.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("MenuControl", "[unit]") {
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe));
    leviathan::gui::MenuControl subject(eventBrokerMock.get());

    SECTION("subscribes to an event producer for certain input event types") {
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_GUI_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);
    }

    SECTION("#add") {
        SECTION("it adds a blank menu") {}
        SECTION("it adds a menu to an existing parent menu") {}
    }

    SECTION("#addButton") {
        SECTION("it adds a button to a menu") {}
    }

    SECTION("#disable") {
        SECTION("it hides a menu from view and from events") {}
    }

    SECTION("#enable") {
        SECTION("it makes a menu visible for view and events") {}
    }

    SECTION("#draw") {
        SECTION("it draws the visible menues onto the screen") {}
    }
}
