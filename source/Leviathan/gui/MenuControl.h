/*! \file MenuControl.h
 *  \brief Erstellen und Verwalten von Menüs.
 *  \note Bestandteil der Leviathan Engine.
 */

#ifndef LEVIATHAN_GUI_MENUCONTROL_H
#define LEVIATHAN_GUI_MENUCONTROL_H

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
             *  \param producer: produziert (versendet) Events
             */
            explicit MenuControl(input::IEventProducer& producer);

            MenuControl() = delete;
            ~MenuControl() = default;
            MenuControl(const MenuControl&) = delete;
            MenuControl& operator=(const MenuControl&) = delete;

            /*! \brief Reagiert auf Events vom Producer.
             *  \param event: Input-Event
             *  \return `true` wenn es zu diesem Event eine Aktion mit mindestens einem Empfänger gibt, ansonsten
             * `false`
             */
            bool onEvent(const irr::SEvent& event);
        };
    }
}
#endif
