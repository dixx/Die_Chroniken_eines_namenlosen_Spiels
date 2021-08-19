/*! \file MenuControl.h
 *  \brief Erstellen und Verwalten von Menüs.
 *  \note Bestandteil der Leviathan Engine.
 */

#ifndef LEVIATHAN_GUI_MENUCONTROL_H
#define LEVIATHAN_GUI_MENUCONTROL_H

#include "../input/IEventConsumer.h"
#include "../input/IEventProducer.h"
#include "../video/Textures.h"
#include "Menu.h"
#include "irrlicht.h"
#include <gui/IMenuControl.h>
#include <map>
#include <memory>
#include <string>

namespace leviathan {
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
                input::IEventProducer& producer, leviathan::video::Textures& textures);

            ~MenuControl();

            MenuControl() = delete;
            MenuControl(const MenuControl&) = delete;
            MenuControl& operator=(const MenuControl&) = delete;

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
            void addMenu(const wchar_t* name, const MenuConfiguration& config);

            /*! \brief Fügt einem Menü einen neuen Button hinzu.
             *  \param menuName: Bezeichner/Identifikator für das Menü
             *  \param buttonName: Bezeichner/Identifikator für den neuen Button
             *  \param config: Definition des Erscheinungsbildes des neuen Buttons
             */
            void addButton(const wchar_t* menuName, const wchar_t* buttonName, const ButtonConfiguration& config);

            /*! \brief Macht das Menü sichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            void enable(const wchar_t* name);

            /*! \brief Macht das Menü unsichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            void disable(const wchar_t* name);

            /*! \brief Zeichnet alle aktiven Menüs auf den Bildschirm.
             */
            void draw();

        private:
            irr::gui::IGUIEnvironment* _guiEnv = nullptr;
            irr::video::IVideoDriver* _videoDriver = nullptr;
            input::IEventProducer& _producer;
            leviathan::video::Textures& textures_;
            std::map<std::wstring, std::unique_ptr<Menu>> _menus = std::map<std::wstring, std::unique_ptr<Menu>>();

            irr::video::ITexture* loadTexture(const std::string& filename, bool makeTransparent);
        };
    }
}
#endif
