/*! \file IGround.h
 *  \brief Bietet Zugriff auf begehbaren Boden.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_IGROUND_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_IGROUND_H

#include <video/IPositionable.h>

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;
    }

    namespace world {
        struct Node3DConfiguration;

        /*! \interface IGround
         *  \brief Bietet Zugriff auf begehbaren Boden
         */
        struct IGround {
            virtual ~IGround() {}

            /*! \brief Fügt ein Kartenteil hinzu.
             *  \param tileConfig: Eigenschaften des Kartenteils
             */
            virtual void add(const Node3DConfiguration& tileConfig) = 0;

            /*! \brief Entfernt alle Kartenteile aus dem Spiel und gibt den Speicher frei.
             */
            virtual void unload() = 0;

            /*! \brief Gibt die Höhe des Bodens (Y-Koordinate, virtuelle Einheiten) an der gegebenen Position an.
             *  \param position: Position deren Höhe ermittelt werden soll
             *  \return Höhe des Bodens an der gegebenen Position
             */
            virtual float getHeight(const video::Vector3D& position) const = 0;

            /*! \brief Passt die Höhe der aktuellen Position an die Höhe des Bodens an.
             *  \param object: Object, dessen Position angepasst werden soll.
             */
            virtual void adjustHeight(video::IPositionable& object) const = 0;
        };
    }
}

#endif
