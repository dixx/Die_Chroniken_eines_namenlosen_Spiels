/*! \file MenuControl.h
 *  \brief Erstellen und Verwalten von Menüs.
 *  \note Bestandteil der Leviathan Engine.
 */

#ifndef LEVIATHAN_GUI_MENUCONTROL_H
#define LEVIATHAN_GUI_MENUCONTROL_H

#include <map>
#include <memory>
#include <string>
#include "../input/IEventConsumer.h"
#include "../input/IEventProducer.h"
#include "irrlicht.h"

namespace leviathan {
    namespace gui {

        /*! \class MenuControl MenuControl.h "MenuControl.h"
         *  \brief Diese Klasse enthält Funktionen zum Erstellen und Verwalten von Menüs.
         */
        class MenuControl : public input::IEventConsumer {

        public:
            /*! \brief Konstruktor.
             *  \param guiEnv: Zeiger auf die GUI-Umgebung der Graphic Engine
             *  \param producer: produziert (versendet) Events
             */
            MenuControl(irr::gui::IGUIEnvironment* guiEnv, input::IEventProducer& producer);

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
             *  \return Zeiger auf das neue Menü
             */
            irr::gui::IGUIElement* addMenu(const char* name);

            /*! \brief Macht das Menü sichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            void enable(const char* name);

            /*! \brief Macht das Menü unsichtbar für Anzeige und Interaktionen.
             *  \param name: Bezeichner/Identifikator für das neue Menü
             */
            void disable(const char* name);

            /*! \brief Zeichnet das Menü auf den Bildschirm.
             */
            void draw();

        private:
            irr::gui::IGUIEnvironment* _guiEnv = nullptr;
            input::IEventProducer& _producer;
            std::map<std::string, irr::gui::IGUIElement*> _menus = std::map<std::string, irr::gui::IGUIElement*>();
        };
    }
}
#endif
