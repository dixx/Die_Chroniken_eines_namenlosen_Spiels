/*! \file MenuControl.h
 *  \brief Erstellen und Verwalten von Menüs.
 *  \note Bestandteil der Leviathan Engine.
 */

#ifndef LEVIATHAN_GUI_MENUCONTROL_H
#define LEVIATHAN_GUI_MENUCONTROL_H

#include "../input/IEventConsumer.h"
#include "Menu.h"
#include <gui/IMenuControl.h>
#include <map>
#include <memory>
#include <string>

namespace irr {
    namespace gui {
        class IGUIEnvironment;
    }
    namespace video {
        class ITexture;
        class IVideoDriver;
    }
}

namespace leviathan {
    namespace input {
        struct IEventProducer;
    }
    namespace video {
        class Textures;
    }

    namespace gui {

        /*! \class MenuControl MenuControl.h "MenuControl.h"
         *  \brief Diese Klasse enthält Funktionen zum Erstellen und Verwalten von Menüs.
         */
        class MenuControl final : public IMenuControl, public input::IEventConsumer {
        public:
            /*! \brief Konstruktor.
             *  \param guiEnv: Zeiger auf die GUI-Umgebung der Graphic Engine
             *  \param videoDriver: Zeiger auf den Videotreiber der Graphic Engine
             *  \param producer: produziert (versendet) Events
             *  \param textures: Instanz der Texturenverwaltung
             */
            MenuControl(irr::gui::IGUIEnvironment* guiEnv, irr::video::IVideoDriver* videoDriver,
                input::IEventProducer& producer, video::Textures& textures);

            ~MenuControl();

            MenuControl() = delete;
            MenuControl(const MenuControl&) = delete;
            MenuControl(const MenuControl&&) = delete;
            MenuControl& operator=(const MenuControl&) = delete;
            MenuControl& operator=(const MenuControl&&) = delete;

            /*! \brief Reagiert auf Events vom Producer.
             *  \param event: Input-Event
             *  \return `true` wenn es zu diesem Event eine Aktion mit mindestens einem Empfänger gibt, ansonsten
             *          `false`
             */
            bool onEvent(const irr::SEvent& event);

            /*! \brief Fügt ein neues Menü hinzu.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             *  \param config: Definition des Erscheinungsbildes des neuen Menüs
             */
            void addMenu(const wchar_t* name, const MenuConfiguration& config) override;

            /*! \brief Fügt einem Menü einen neuen Button hinzu.
             *  \param menuName: Bezeichner/Identifikator für das Menü
             *  \param buttonName: Bezeichner/Identifikator für den neuen Button
             *  \param config: Definition des Erscheinungsbildes des neuen Buttons
             */
            void addButton(
                const wchar_t* menuName, const wchar_t* buttonName, const ButtonConfiguration& config) override;

            /*! \brief Macht das Menü sichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            void enable(const wchar_t* name) override;

            /*! \brief Macht das Menü unsichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            void disable(const wchar_t* name) override;

            /*! \brief Zeichnet alle aktiven Menüs auf den Bildschirm.
             */
            void draw() override;

        private:
            irr::gui::IGUIEnvironment* mGuiEnv = nullptr;
            irr::video::IVideoDriver* mVideoDriver = nullptr;
            input::IEventProducer& mProducer;
            video::Textures& mTextures;
            std::map<std::wstring, std::unique_ptr<Menu>> mMenues = std::map<std::wstring, std::unique_ptr<Menu>>();

            irr::video::ITexture* loadTexture(const std::string& filename, bool makeTransparent);
        };
    }
}
#endif
