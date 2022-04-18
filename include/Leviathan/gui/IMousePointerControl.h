/*! \file IMousePointerControl.h
 *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers.
 *  \note Bestandteil der Leviathan Engine
 */
#ifndef LEVIATHAN_PUBLIC_INTERFACES_GUI_IMOUSEPOINTER_H
#define LEVIATHAN_PUBLIC_INTERFACES_GUI_IMOUSEPOINTER_H

#include <cstdint>

namespace leviathan {
    namespace video {
        struct Position2D;
    }

    namespace gui {
        struct MousePointerConfiguration;

        /*! \interface IMousePointerControl
         *  \brief Bietet Zugriff auf die Darstellung des Mauszeigers
         */
        struct IMousePointerControl {
            virtual ~IMousePointerControl() {}

            /*! \brief Erstellt einen anzeigbaren Mauszeiger aus einem Bild.
             *  \param id: ID des Mauszeigers
             *  \param configuration: Mauszeiger-Konfiguration
             */
            virtual void addMousePointer(const uint32_t id, const MousePointerConfiguration& configuration) = 0;

            /*! \brief Wählt den anzuzeigenden Mauspfeil aus.
             *  \param id: ID des anzuzeigenden Mauszeigers
             */
            virtual void setActiveMousPointer(const uint32_t id) = 0;

            /*! \brief Gibt die aktuelle Bildschirmposition des Mauszeigers zurück.
             *  \return Bildschirm-Koordinaten in Pixel
             */
            virtual const video::Position2D getPosition() const = 0;

            /*! \brief Zeichnet den Mauszeiger auf den Bildschirm.
             */
            virtual void draw() = 0;
        };
    }
}

#endif
