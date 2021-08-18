/*! \file IHero.h
 *  \brief Ein Held.
 */

#ifndef LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_IHERO_H
#define LEVIATHAN_PUBLIC_INTERFACES_CHARACTERS_IHERO_H

#include <string>
#include <video/Vector3D.h>

namespace leviathan {
    namespace characters {
        /*! \interface IHero
         *  \brief Diese Schnittstelle bietet Zugriff auf einen Helden.
         */
        struct IHero {
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

            /*! \brief Gibt die aktuelle Position zurück, relativ zum Welt-Hauptknoten.
             */
            virtual video::Position3D getPosition() const = 0;

            /*! \brief Setzt die Position neu, relativ zum Welt-Hauptknoten.
             *  \param position: gewünschte neue Position
             */
            virtual void setPosition(const video::Position3D& position) = 0;

            /*! \brief Gibt die aktuellen Rotationswerte zurück.
             */
            virtual video::Rotation3D getRotation() const = 0;

            /*! \brief Setzt die Rotationswerte neu.
             *  \param rotation: gewünschte neue Rotationen in °
             */
            virtual void setRotation(const video::Rotation3D& rotation) = 0;
        };
    }
}
#endif
