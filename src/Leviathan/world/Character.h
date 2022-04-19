/*! \file Character.h
 *  \brief Ein 3D-Objekt, welches einen spielbaren Charakter oder ein Monster repräsentiert.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_CHARACTER_H
#define LEVIATHAN_WORLD_CHARACTER_H

#include <string>
#include <video/Vector3D.h>
#include <world/INode3D.h>

namespace irr {
    namespace scene {
        class ISceneManager;
        class IAnimatedMeshSceneNode;
    }
}

namespace leviathan {
    namespace characters {
        struct CharacterConfiguration;
    }
    namespace video {
        class Textures;
    }

    namespace world {

        /*! \class Character
         *  \brief Ein 3D-Objekt, welches einen spielbaren Charakter oder ein Monster repräsentiert.
         */
        class Character : public INode3D {
        public:
            Character(const characters::CharacterConfiguration& characterConfig, video::Textures& textures,
                irr::scene::ISceneManager* sceneManager);

            ~Character();

            Character(const Character&) = default;
            Character(Character&&) = default;
            Character& operator=(const Character&) = default;
            Character& operator=(Character&&) = default;

            void setDesiredPostition(const video::Position3D& targetPosition) override;

            void setPosition(const video::Position3D& position);

            void setVisible();

            void setInvisible();

            std::string getName() const;

            video::Position3D getPosition() const;

            video::Rotation3D getRotation() const;

            void setRotation(const video::Rotation3D& rotation);

        private:
            video::Position3D mDesiredPosition = video::Position3D();
            video::Vector3D mOffset = video::Vector3D();
            irr::scene::IAnimatedMeshSceneNode* mCharacterNode = nullptr;

            void createNode(const characters::CharacterConfiguration& config, irr::scene::ISceneManager* sceneManager);
            void setScale(const video::Scale3D& scale);
        };
    }
}
#endif
