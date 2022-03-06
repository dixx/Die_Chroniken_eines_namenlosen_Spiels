/*! \file ICollider.h
 *  \brief Bietet Zugriff auf Kollisionserkennung.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_WORLD_ICOLLIDER_H
#define LEVIATHAN_PUBLIC_INTERFACES_WORLD_ICOLLIDER_H

namespace leviathan {
    namespace video {
        struct Position2D;
    }

    namespace world {
        struct Collision;

        /*! \interface ICollider
         *  \brief Bietet Zugriff auf Kollisionserkennung.
         */
        struct ICollider {
            virtual ~ICollider() {}

            /*! \brief Prüft Kollision der Welt mit einem Strahl, welcher in der aktiven Kamera beginnt und durch
             *         die übergebenen Bildschirm-Koordinaten führt.
             *  \note Nur aktive, kollidierbare Knoten werden geprüft.
             *  \param screenCoordinates: Bildschirm-Koordinaten, in Pixel
             *  \return Kollisionsobjekt
             */
            virtual Collision getCollisionFromScreenCoordinates(const video::Position2D& screenCoordinates) const = 0;
        };
    }
}
#endif
