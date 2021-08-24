#include "Hero.h"
#include "../world/Character.h"
#include "../world/NodeManager.h"
#include <characters/CharacterConfiguration.h>

namespace leviathan {
    namespace characters {
        Hero::Hero(const CharacterConfiguration& characterConfig, world::NodeManager& nodeManager)
        : node_(nodeManager.createHeroNode(characterConfig)) {}

        void Hero::enablePlayableCharacter() {
            node_.setVisible();
        }

        void Hero::disablePlayableCharacter() {
            node_.setInvisible();
        }

        const std::string Hero::getInternalName() const {
            return node_.getName();
        }

        video::Position3D Hero::getPosition() const {
            return node_.getPosition();
        }

        void Hero::setPosition(const video::Position3D& position) {
            node_.setPosition(position);
        }

        video::Rotation3D Hero::getRotation() const {
            return node_.getRotation();
        }

        void Hero::setRotation(const video::Rotation3D& rotation) {
            node_.setRotation(rotation);
        }
    }
}
