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

    // enum guiItemIds {
    //     GUI_SOME_BUTTON = 101,
    //     GUI_ANOTHER_BUTTON
    // };

    leviathan::gui::MenuControl subject(&guiEnvironmentSpy.get(), eventBrokerMock.get());

    SECTION("subscribes to an action producer for certain input event types") {
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_GUI_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);
    }

    SECTION("#add adds a blank menu") {
        When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu, &anotherMenu);

        auto result = subject.add("some menue");
        REQUIRE(result == &menu);
        REQUIRE(result->getParent() == rootElement);
        REQUIRE(result->getChildren().size() == 0);
        result = subject.add("some other menue");
        REQUIRE(result == &anotherMenu);
        REQUIRE(result->getParent() == rootElement);
        REQUIRE(result->getChildren().size() == 0);
    }

    SECTION("#addButton adds a button to a menu") {
    }

    SECTION("#disable hides a menu from view and from events") {
    }

    SECTION("#enable makes a menu visible for view and events") {
    }

    SECTION("#draw displays the visible menues onto the screen") {
    }


    // TODO: onAction must be tested elsewhere
}
