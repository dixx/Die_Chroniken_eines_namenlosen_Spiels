#include "../../src/Leviathan/gui/MenuControl.h"
#include "../../src/Leviathan/input/IEventProducer.h"
#include "../../src/Leviathan/video/Textures.h"
#include "../helpers/IGUIImageMock.hpp"
#include "../helpers/IImageMock.hpp"
#include "../helpers/TestHelper.h"
#include "IVideoDriver.h"
#include "fakeit.hpp"
#include <memory>

using namespace fakeit;

#define addImageArgs \
    irr::gui::IGUIImage*(const irr::core::rect<irr::s32>&, irr::gui::IGUIElement*, irr::s32, const wchar_t*, bool)
#define makeColorKeyTextureArgs void(irr::video::ITexture*, irr::video::SColor, bool)
#define getTextureArgs irr::video::ITexture*(const irr::io::path&)
#define addTextureArgs irr::video::ITexture*(const irr::io::path&, irr::video::IImage*, void*)
#define createImageArgs \
    irr::video::IImage*(irr::video::ITexture*, const irr::core::position2di&, const irr::core::dimension2du&)
/*
#define addButtonArgs irr::gui::IGUIButton*(const irr::core::rect<irr::s32>&, irr::gui::IGUIElement*, irr::s32, \
                                          const wchar_t*, const wchar_t*)
*/

TEST_CASE("MenuControl", "[unit]") {
    Mock<irr::gui::IGUIEnvironment> guiEnvironmentMock;
    Fake(Method(guiEnvironmentMock, addEmptySpriteBank), Method(guiEnvironmentMock, getRootGUIElement));
    Mock<irr::video::IVideoDriver> videoDriverMock;
    leviathan::video::Textures textures(&videoDriverMock.get(), TestHelper::Logger());
    Mock<leviathan::input::IEventProducer> eventBrokerMock;
    Fake(Method(eventBrokerMock, subscribe), Method(eventBrokerMock, unsubscribe));

    SECTION("subscribes and unsubscribes to an action producer for certain input event types") {
        auto subject = new leviathan::gui::MenuControl(
            &guiEnvironmentMock.get(), &videoDriverMock.get(), eventBrokerMock.get(), textures);
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_GUI_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, subscribe).Using(_, irr::EET_KEY_INPUT_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);

        delete subject;
        // FIXME issue with the mock when .Using(subject, ...) instead of .Using(_, ...)
        Verify(Method(eventBrokerMock, unsubscribe).Using(_, irr::EET_GUI_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, unsubscribe).Using(_, irr::EET_MOUSE_INPUT_EVENT)).Exactly(Once);
        Verify(Method(eventBrokerMock, unsubscribe).Using(_, irr::EET_KEY_INPUT_EVENT)).Exactly(Once);
        VerifyNoOtherInvocations(eventBrokerMock);
    }

    SECTION("Menu manipulation") {
        Fake(Method(videoDriverMock, setTextureCreationFlag));
        leviathan::gui::MenuConfiguration menuConfig({{320, 200}, {300, 400}, "../path/to.img", {70, 60}, true});
        irr::gui::IGUIElement menu(
            irr::gui::EGUIET_MODAL_SCREEN, &guiEnvironmentMock.get(), nullptr, 42, irr::core::recti());
        mocks::IGUIImageMock backgroundImage(&guiEnvironmentMock.get(), nullptr, 123, irr::core::recti());
        When(OverloadedMethod(guiEnvironmentMock, addImage, addImageArgs)).AlwaysReturn(&backgroundImage);
        Fake(ConstOverloadedMethod(videoDriverMock, makeColorKeyTexture, makeColorKeyTextureArgs));
        When(OverloadedMethod(videoDriverMock, getTexture, getTextureArgs)).AlwaysReturn(nullptr);
        When(OverloadedMethod(videoDriverMock, addTexture, addTextureArgs)).AlwaysReturn(nullptr);
        mocks::IImageMock image;
        When(OverloadedMethod(videoDriverMock, createImage, createImageArgs)).AlwaysReturn(&image);
        When(Method(guiEnvironmentMock, addModalScreen)).Return(&menu);

        leviathan::gui::MenuControl subject(
            &guiEnvironmentMock.get(), &videoDriverMock.get(), eventBrokerMock.get(), textures);

        SECTION("#addMenu adds a modal screen as menu root") {
            irr::gui::IGUIElement anotherMenu(
                irr::gui::EGUIET_MODAL_SCREEN, &guiEnvironmentMock.get(), nullptr, 43, irr::core::recti());
            When(Method(guiEnvironmentMock, addModalScreen)).Return(&menu, &anotherMenu);

            subject.addMenu(L"some menu", menuConfig);
            subject.addMenu(L"some other menu", menuConfig);
            Verify(Method(guiEnvironmentMock, addModalScreen)).Exactly(2_Times);
            Verify(OverloadedMethod(guiEnvironmentMock, addImage, addImageArgs).Using(_, &menu, -1, nullptr, true))
                .Once();

            SECTION("menu root is disabled for events") {
                REQUIRE_FALSE(menu.isEnabled());
            }
        }

        SECTION("#enable makes a menu visible") {
            subject.addMenu(L"some menu", menuConfig);
            subject.enable(L"some menu");
            REQUIRE(menu.isVisible());
            REQUIRE_FALSE(menu.isEnabled());
        }

        SECTION("#disable hides a menu from view") {
            subject.addMenu(L"some menu", menuConfig);
            subject.disable(L"some menu");
            REQUIRE_FALSE(menu.isVisible());
            REQUIRE_FALSE(menu.isEnabled());
        }

        SECTION("#draw displays the visible menues onto the screen") {
            // Mock<irr::gui::IGUIElement> menuSpy(menu);
            subject.addMenu(L"some menu", menuConfig);
            subject.draw();
            // Verify(Method(menuSpy, draw)).Once();
            // not testable atm, because: Can't mock a type with multiple inheritance
        }

        SECTION("#addButton adds a button to a menu") {
            // Mock<leviathan::input::IEventProducer> eventBrokerMock;
            // Fake(Method(eventBrokerMock, subscribe), Method(eventBrokerMock, unsubscribe));
            // mocks::GUIEnvironmentMock guiEnvironmentMock;
            // Mock<mocks::GUIEnvironmentMock> guiEnvironmentSpy(guiEnvironmentMock);
            // // Mock<irr::video::ITexture> textureMock;
            // mocks::VideoDriverMock videoDriverMock;
            // Mock<mocks::VideoDriverMock> videoDriverSpy(videoDriverMock);
            // leviathan::gui::MenuControl subject(&guiEnvironmentSpy.get(), &videoDriverSpy.get(),
            // eventBrokerMock.get()); Mock<mocks::VideoDriverMock> videoDriverSpy(videoDriverMock);
            // When(OverloadedMethod(videoDriverSpy, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
            // Fake(OverloadedMethod(guiEnvironmentSpy, addImage, addImageArgs));
            // irr::gui::IGUIElement* button = new irr::gui::IGUIElement(
            //     irr::gui::EGUIET_BUTTON, &guiEnvironmentSpy.get(), &menu, 42, irr::core::recti()
            // );
            // When(Method(guiEnvironmentSpy, addButton)).AlwaysReturn(static_cast<irr::gui::IGUIButton*>(button));

            leviathan::gui::ButtonConfiguration buttonConfig(
                {{40, 10}, {300, 400}, "../path/to.img", {30, 20}, {70, 60}, true});
            // subject.addMenu(L"some menu", menuConfig);
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
}
