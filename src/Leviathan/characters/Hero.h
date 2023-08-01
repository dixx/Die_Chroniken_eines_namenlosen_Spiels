/*! \file Hero.h
 *  \brief Ein Held.
 */

#ifndef LEVIATHAN_CHARACTERS_HERO_H
#define LEVIATHAN_CHARACTERS_HERO_H

#include <characters/IHero.h>
#include <string>
#include <video/Vector3D.h>
#include <video/Vector3DCompatible.h>

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
            Hero(const Hero&&) = delete;
            Hero& operator=(const Hero&) = delete;
            Hero& operator=(const Hero&&) = delete;

            void enablePlayableCharacter() override;

            void disablePlayableCharacter() override;

            const std::string getInternalName() const override;

            video::Position3D getPosition() const override;

            void setPosition(const video::Position3D& position) override;

            video::Rotation3D getRotation() const override;

            void setRotation(const video::Rotation3D& rotation) override;

            void moveTo(const video::Position3D& position) override;

            void update(const float elapsedSeconds) override;

        private:
            world::Character& mNode;
            float mLocomotionSpeed = 3.2f;
            video::Position3DCompatible mTargetPosition = video::Position3DCompatible({});
            video::Rotation3DCompatible mRotationOffset = video::Rotation3DCompatible({});
            bool mIsMoving = false;
        };
    }
}
#endif
