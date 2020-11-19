/*! \file Hero.h
 *  \brief Ein Held.
 */

#ifndef LEVIATHAN_GAME_HERO_H
#define LEVIATHAN_GAME_HERO_H

#include "irrlicht.h"
#include <string>

namespace leviathan {
    namespace characters {
        /*! \class Hero Hero.h "Hero.h"
         *  \brief Diese Klasse bildet einen Helden ab.
         */
        class Hero {
        public:
            /*! \brief Konstruktor
             *  \param internalName: interner Name des Helden
             *  \param sceneManager: Szenen-Manager des initialisierten Irrlicht Device
             */
            Hero(const std::string& internalName, irr::scene::ISceneManager* sceneManager);

            /*! \brief Aktualisiert den Helden.
             */
            void update();

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
            irr::core::vector3df getPosition() const;

            /*! \brief Setzt die Position neu, relativ zum Welt-Hauptknoten.
             *  \param position: gewünschte neue Position
             */
            void setPosition(const irr::core::vector3df& position);

            /*! \brief Gibt den aktuellen Rotationsvektor zurück.
             */
            irr::core::vector3df getRotation() const;

            /*! \brief Setzt den Rotationsvektor neu.
             *  \param rotation: gewünschte neue Rotation
             */
            void setRotation(const irr::core::vector3df& rotation);

        private:
            irr::scene::IAnimatedMeshSceneNode* node_ = nullptr;
        };
    }
}
#endif
