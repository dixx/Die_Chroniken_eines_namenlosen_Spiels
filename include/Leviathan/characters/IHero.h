/*! \file IHero.h
 *  \brief Ein Held.
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_IHERO_H
#define LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_IHERO_H

#include <string>
#include <video/IPositionable.h>

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;
        using Rotation3D = Vector3D;
    }

    namespace characters {
        /*! \interface IHero
         *  \brief Diese Schnittstelle bietet Zugriff auf einen Helden.
         */
        struct IHero : video::IPositionable {
            virtual ~IHero() {}

            /*! \brief Macht den spielbaren Szenenknoten des Helden sichtbar.
             */
            virtual void enablePlayableCharacter() = 0;

            /*! \brief Macht den spielbaren Szenenknoten des Helden unsichtbar.
             */
            virtual void disablePlayableCharacter() = 0;

            /*! \brief Gibt den internen Namen des Helden zurück.
             */
            virtual const std::string getInternalName() const = 0;

            /*! \brief Gibt die aktuellen Rotationswerte zurück.
             */
            virtual video::Rotation3D getRotation() const = 0;

            /*! \brief Setzt die Rotationswerte neu.
             *  \param rotation: gewünschte neue Rotationen in °
             */
            virtual void setRotation(const video::Rotation3D& rotation) = 0;

            /*! \brief Setzt die Zielposition neu, relativ zum Welt-Hauptknoten.
             *  \param position: gewünschte neue Position, zu welcher der Held sich bewegen soll
             */
            virtual void moveTo(const video::Position3D& position) = 0;

            /*! \brief Aktualisiert Position des Helden, falls dieser sich bewegt.
             *  \param elapsedSeconds: Dauer des letzten Frames, in Sekunden
             */
            virtual void update(const float elapsedSeconds) = 0;
        };
    }
}
#endif
