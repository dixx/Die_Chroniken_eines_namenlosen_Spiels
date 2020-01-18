#include "../../source/Leviathan/gui/MenuControl.h"
#include "../../source/Leviathan/input/Actions.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "../helpers/GUIEnvironmentMock.hpp"
#include "irrlicht.h"
#include <memory>

using namespace fakeit;

TEST_CASE("MenuControl", "[unit]") {
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe), Method(eventBrokerMock, unsubscribe));
    mocks::GUIEnvironmentMock guiEnvironmentMock;
    Mock<mocks::GUIEnvironmentMock> guiEnvironmentSpy(guiEnvironmentMock);
    irr::gui::IGUIElement* rootElement = guiEnvironmentSpy.get().getRootGUIElement();
    irr::gui::IGUIElement menu = irr::gui::IGUIElement(
        irr::gui::EGUIET_MODAL_SCREEN, nullptr, rootElement, 42, irr::core::recti());
    irr::gui::IGUIElement anotherMenu = irr::gui::IGUIElement(
        irr::gui::EGUIET_MODAL_SCREEN, nullptr, rootElement, 43, irr::core::recti());

    leviathan::gui::MenuControl subject(&guiEnvironmentSpy.get(), eventBrokerMock.get());

    SECTION("subscribes to an action producer for certain input event types") {
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_GUI_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);
    }

    SECTION("#addMenu adds a blank menu") {
        When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu, &anotherMenu);

        subject.addMenu("some menu");
        subject.addMenu("some other menu");
        Verify(Method(guiEnvironmentSpy, addModalScreen).Using(rootElement)).Exactly(2_Times);
    }

    SECTION("#disable hides a menu from view and from events") {
        When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu);
        subject.addMenu("some menu");
        REQUIRE(menu.isVisible());
        REQUIRE(menu.isEnabled());

        subject.disable("some menu");
        REQUIRE_FALSE(menu.isVisible());
        REQUIRE_FALSE(menu.isEnabled());

        SECTION("#enable makes a menu visible for view and events") {
            subject.enable("some menu");
            REQUIRE(menu.isVisible());
            REQUIRE(menu.isEnabled());
        }
    }

    SECTION("#draw displays the visible menues onto the screen") {
        When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu, &anotherMenu);
        subject.addMenu("some menu");
        subject.addMenu("some other menu");
        subject.disable("some other menu");
        subject.draw();
        // not testable atm, because: Can't mock a type with multiple inheritance
    }
}
