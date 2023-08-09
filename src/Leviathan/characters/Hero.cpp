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
            mTargetPosition = position;
        }

        video::Rotation3D Hero::getRotation() const {
            return mCharacterNode.getRotation();
        }

        void Hero::setRotation(const video::Rotation3D& rotation) {
            mCharacterNode.setRotation(rotation);
        }

        void Hero::update(const float elapsedSeconds) {
            if (!mIsMoving) return;

            video::Position3DCompatible position = mCharacterNode.getPosition();
            auto distanceLeft = (mTargetPosition - position).toIrrlichtVector();
            if (distanceLeft.equals({0.0f, 0.0f, 0.0f}, 0.3f)) {
                mIsMoving = false;
                mTargetPosition = position;
                // mCharacterNode.setMD2Animation( irr::scene::EMAT_STAND );
            } else {
                // move
                auto nextStep = distanceLeft.setLength(mLocomotionSpeed * elapsedSeconds);
                mCharacterNode.setPosition(position + nextStep);
            }
        }

        void Hero::moveTo(const video::Position3D& position) {
            mTargetPosition = position;
            mIsMoving = true;
            // mCharacterNode.setMD2Animation( irr::scene::EMAT_RUN );
            video::Position3DCompatible currentPosition = mCharacterNode.getPosition();
            auto direction = (mTargetPosition - currentPosition).toIrrlichtVector();
            direction.Y = 0.0f;
            auto rotation = direction.getHorizontalAngle();
            mCharacterNode.setRotation(video::Rotation3DCompatible(rotation));
        }
    }
}
