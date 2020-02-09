#include "../../source/Leviathan/gui/MenuControl.h"
#include "../../source/Leviathan/input/Actions.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "../helpers/GUIEnvironmentMock.hpp"
#include "../helpers/VideoDriverMock.hpp"
#include "irrlicht.h"
#include <memory>

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)
#define addImageArgs irr::gui::IGUIImage*(const irr::core::rect<irr::s32>&, irr::gui::IGUIElement*, irr::s32, \
                                          const wchar_t*, bool)
#define addButtonArgs irr::gui::IGUIButton*(const irr::core::rect<irr::s32>&, irr::gui::IGUIElement*, irr::s32, \
                                          const wchar_t*, const wchar_t*)

TEST_CASE("MenuControl", "[unit]") {
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe), Method(eventBrokerMock, unsubscribe));
    mocks::GUIEnvironmentMock guiEnvironmentMock;
    Mock<mocks::GUIEnvironmentMock> guiEnvironmentSpy(guiEnvironmentMock);
    mocks::VideoDriverMock videoDriverMock;
    Mock<mocks::VideoDriverMock> videoDriverSpy(videoDriverMock);
    irr::gui::IGUIElement* rootElement = guiEnvironmentSpy.get().getRootGUIElement();
    irr::gui::IGUIElement menu = irr::gui::IGUIElement(
        irr::gui::EGUIET_MODAL_SCREEN, nullptr, rootElement, 42, irr::core::recti());
    irr::gui::IGUIElement anotherMenu = irr::gui::IGUIElement(
        irr::gui::EGUIET_MODAL_SCREEN, nullptr, rootElement, 43, irr::core::recti());

    leviathan::gui::MenuControl subject(&guiEnvironmentSpy.get(), &videoDriverSpy.get(), eventBrokerMock.get());
    When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu);

    SECTION("subscribes to an action producer for certain input event types") {
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_GUI_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);
    }

    SECTION("#addMenu adds a blank menu") {
        When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu, &anotherMenu);

        subject.addMenu(L"some menu");
        subject.addMenu(L"some other menu");
        Verify(Method(guiEnvironmentSpy, addModalScreen).Using(rootElement)).Exactly(2_Times);
    }

    SECTION("#disable hides a menu from view and from events") {
        subject.addMenu(L"some menu");
        REQUIRE(menu.isVisible());
        REQUIRE(menu.isEnabled());

        subject.disable(L"some menu");
        REQUIRE_FALSE(menu.isVisible());
        REQUIRE_FALSE(menu.isEnabled());

        SECTION("#enable makes a menu visible for view and events") {
            subject.enable(L"some menu");
            REQUIRE(menu.isVisible());
            REQUIRE(menu.isEnabled());
        }
    }

    SECTION("#draw displays the visible menues onto the screen") {
        When(Method(guiEnvironmentSpy, addModalScreen)).Return(&menu, &anotherMenu);
        subject.addMenu(L"some menu");
        subject.addMenu(L"some other menu");
        subject.disable(L"some other menu");
        subject.draw();
        // not testable atm, because: Can't mock a type with multiple inheritance
    }
}

TEST_CASE("MenuControl Menu manipulation", "[integration]") {
    SECTION("#addButton adds a button to a menu") {
        Mock<leviathan::input::IEventProducer> eventBrokerMock;
        Fake(Method(eventBrokerMock, subscribe), Method(eventBrokerMock, unsubscribe));
        mocks::GUIEnvironmentMock guiEnvironmentMock;
        Mock<mocks::GUIEnvironmentMock> guiEnvironmentSpy(guiEnvironmentMock);
        // Mock<irr::video::ITexture> textureMock;
        mocks::VideoDriverMock videoDriverMock;
        Mock<mocks::VideoDriverMock> videoDriverSpy(videoDriverMock);
        leviathan::gui::MenuControl subject(&guiEnvironmentSpy.get(), &videoDriverSpy.get(), eventBrokerMock.get());
        // Mock<mocks::VideoDriverMock> videoDriverSpy(videoDriverMock);
        // When(OverloadedMethod(videoDriverSpy, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
        // Fake(OverloadedMethod(guiEnvironmentSpy, addImage, addImageArgs));
        // irr::gui::IGUIElement* button = new irr::gui::IGUIElement(
        //     irr::gui::EGUIET_BUTTON, &guiEnvironmentSpy.get(), &menu, 42, irr::core::recti()
        // );
        // When(Method(guiEnvironmentSpy, addButton)).AlwaysReturn(static_cast<irr::gui::IGUIButton*>(button));

        leviathan::gui::ButtonConfiguration buttonConfig(
            {{40, 10}, {300, 400}, "../path/to.img", {30, 20}, {70, 60}, true});
        // subject.addMenu(L"some menu");
        // subject.addButton(L"some menu", L"some button", buttonConfig);

        // delete button;
        // Verify(OverloadedMethod(videoDriverSpy, getTexture, getTextureArgs).Using("../path/to.img")).Once();
        // VerifyNoOtherInvocations(videoDriverSpy);

        // Verify(OverloadedMethod(guiEnvironmentSpy, addImage, addImageArgs)
        //     .Using(irr::core::rect<irr::s32>({300, 400}, {40, 10}), &menu, _, L"some button", true)
        // ).Once();
        // Verify(Method(guiEnvironmentSpy, addButton)
        //     .Using(irr::core::rect<irr::s32>({300, 400}, {40, 10}), &menu, _, _, _)
        // ).Once();
        // VerifyNoOtherInvocations(guiEnvironmentSpy);

        // irr::gui::IGUIImage* menueBgImage = guienv_->addImage(
        //         irr::core::recti( imagePosition, textureSize ),
        //         menuRoot_, ID_MAIN_BGIMAGE, L"Hauptmenü"
        // );
        // menueBgImage->setImage( mainMenuTexture_ );
        // irr::gui::IGUIButton* newButton = guienv_->addButton(
        //         irr::core::recti( irr::core::position2di( 85, 63 ), buttonSize ),
        //         menueBgImage, ID_MAIN_NEWBUTTON, L"Neues Spiel"
        // );
        // not testable atm, because: Can't mock a type with multiple inheritance
    }
}
