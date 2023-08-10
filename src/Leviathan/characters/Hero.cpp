#include "Hero.h"
#include "../video/Vector3DCompatible.h"
#include "../world/Character.h"
#include "../world/NodeManager.h"
#include <characters/CharacterConfiguration.h>

namespace leviathan {
    namespace characters {
        Hero::Hero(const CharacterConfiguration& characterConfig, world::NodeManager& nodeManager)
        : mCharacterNode(nodeManager.createHeroNode(characterConfig)) {}

        void Hero::enablePlayableCharacter() {
            mCharacterNode.setVisible();
        }

        void Hero::disablePlayableCharacter() {
            mCharacterNode.setInvisible();
        }

        const std::string Hero::getInternalName() const {
            return mCharacterNode.getName();
        }

        video::Position3D Hero::getPosition() const {
            return mCharacterNode.getPosition();
        }

        void Hero::setPosition(const video::Position3D& position) {
            mCharacterNode.setPosition(position);
        }

        video::Rotation3D Hero::getRotation() const {
            return mCharacterNode.getRotation();
        }

        void Hero::setRotation(const video::Rotation3D& rotation) {
            mCharacterNode.setRotation(rotation);
        }

        void Hero::update(const float elapsedSeconds) {
            (void)elapsedSeconds;
            //     // mCharacterNode.setMD2Animation( irr::scene::EMAT_STAND );
            //     // mCharacterNode.setMD2Animation( irr::scene::EMAT_RUN );
        }
    }
}
