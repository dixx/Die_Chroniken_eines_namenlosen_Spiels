/*! \file Hero.h
 *  \brief Ein Held.
 */

#ifndef LEVIATHAN_CHARACTERS_HERO_H
#define LEVIATHAN_CHARACTERS_HERO_H

#include <characters/IHero.h>
#include <string>
#include <video/Vector3D.h>

namespace leviathan {
    namespace world {
        class NodeManager;
        class Character;
    }

    namespace characters {
        struct CharacterConfiguration;

        /*! \class Hero Hero.h "Hero.h"
         *  \brief Diese Klasse bildet einen Helden ab.
         */
        class Hero final : public IHero {
        public:
            /*! \brief Konstruktor
             *  \param characterConfig: Konfiguration des Helden-Szenenknotens
             *  \param nodeManager: Instanz der 3D-Szenenknoten-Verwaltung
             */
            Hero(const CharacterConfiguration& characterConfig, world::NodeManager& nodeManager);

            ~Hero() = default;

            Hero() = delete;
            Hero(const Hero&) = delete;
            Hero& operator=(const Hero&) = delete;

            /*! \brief Macht den spielbaren Szenenknoten des Helden sichtbar.
             */
            void enablePlayableCharacter();

            /*! \brief Macht den spielbaren Szenenknoten des Helden unsichtbar.
             */
            void disablePlayableCharacter();

            /*! \brief Gibt den internen Namen des Helden zurück.
             */
            const std::string getInternalName() const;

            /*! \brief Gibt die aktuelle Position zurück, relativ zum Welt-Hauptknoten.
             */
            video::Position3D getPosition() const;

            /*! \brief Setzt die Position neu, relativ zum Welt-Hauptknoten.
             *  \param position: gewünschte neue Position
             */
            void setPosition(const video::Position3D& position);

            /*! \brief Gibt den aktuellen Rotationsvektor zurück.
             */
            video::Rotation3D getRotation() const;

            /*! \brief Setzt den Rotationsvektor neu.
             *  \param rotation: gewünschte neue Rotation
             */
            void setRotation(const video::Rotation3D& rotation);

        private:
            world::Character& node_;
        };
    }
}
#endif
