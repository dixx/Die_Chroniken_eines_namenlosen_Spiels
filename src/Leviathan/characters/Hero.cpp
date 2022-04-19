#include "Hero.h"
#include "../world/Character.h"
#include "../world/NodeManager.h"
#include <characters/CharacterConfiguration.h>
#include <video/Vector3D.h>

namespace leviathan {
    namespace characters {
        Hero::Hero(const CharacterConfiguration& characterConfig, world::NodeManager& nodeManager)
        : mNode(nodeManager.createHeroNode(characterConfig)) {}

        void Hero::enablePlayableCharacter() {
            mNode.setVisible();
        }

        void Hero::disablePlayableCharacter() {
            mNode.setInvisible();
        }

        const std::string Hero::getInternalName() const {
            return mNode.getName();
        }

        video::Position3D Hero::getPosition() const {
            return mNode.getPosition();
        }

        void Hero::setPosition(const video::Position3D& position) {
            mNode.setPosition(position);
        }

        video::Rotation3D Hero::getRotation() const {
            return mNode.getRotation();
        }

        void Hero::setRotation(const video::Rotation3D& rotation) {
            mNode.setRotation(rotation);
        }
    }
}
