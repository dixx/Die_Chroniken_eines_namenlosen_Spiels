/*! \file IMousePointerControl.h
 *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers.
 *  \note Bestandteil der Leviathan Engine
 */
#ifndef LEVIATHAN_PUBLIC_INTERFACES_GUI_IMOUSEPOINTER_H
#define LEVIATHAN_PUBLIC_INTERFACES_GUI_IMOUSEPOINTER_H

#include "irrlicht.h"
#include <cstdint>

namespace leviathan {
    namespace gui {

        /*! \interface IMousePointerControl
         *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers
         */
        struct IMousePointerControl {
            virtual ~IMousePointerControl() {}

            /*! \brief Erstellt einen anzeigbaren Mauszeiger aus einem Bild.
             *  \param id: ID des Mauszeigers
             *  \param imageFileName: Dateiname (mit Pfad) des Ausgangsbildes
             *  \param imageArea: zu verwendender Bildausschnitt
             *  \param hotSpot: Punkt innerhalb des resultierenden Bildausschnittes, der als "Mauszeiger-Spitze" dient
             */
            virtual void addMousePointer(const uint32_t id, const char* imageFileName,
                const irr::core::recti& imageArea, const irr::core::vector2di& hotSpot) = 0;

            /*! \brief Wählt den anzuzeigenden Mauspfeil aus.
             *  \param id: ID des anzuzeigenden Mauszeigers
             */
            virtual void setActiveMousPointer(const uint32_t id) = 0;

            /*! \brief Zeichnet den Mauszeiger auf den Bildschirm
             */
            virtual void draw() = 0;
        };
    }
}

#endif
