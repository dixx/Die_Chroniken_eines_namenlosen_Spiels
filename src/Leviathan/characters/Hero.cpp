#include "Hero.h"
#include "../video/Vector3DCompatible.h"
#include "../world/Character.h"
#include "../world/NodeManager.h"
#include <characters/CharacterConfiguration.h>

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
            mTargetPosition = position;
        }

        video::Rotation3D Hero::getRotation() const {
            return mNode.getRotation();
        }

        void Hero::setRotation(const video::Rotation3D& rotation) {
            mNode.setRotation(rotation);
        }

        void Hero::update(const float elapsedSeconds) {
            if (!mIsMoving) return;

            video::Vector3D position = mNode.getPosition();
            auto distanceLeft = video::Vector3DCompatible(mTargetPosition - position).toIrrlichtVector();
            if (distanceLeft.equals({0.0f, 0.0f, 0.0f}, 0.3f)) {
                mIsMoving = false;
                mTargetPosition = position;
                // mNode.setMD2Animation( irr::scene::EMAT_STAND );
            } else {
                // move
                auto nextStep = distanceLeft.setLength(mLocomotionSpeed * elapsedSeconds);
                mNode.setPosition(position + video::Vector3DCompatible(nextStep));
            }
        }

        void Hero::moveTo(const video::Position3D& position) {
            mTargetPosition = position;
            mIsMoving = true;
            // mNode.setMD2Animation( irr::scene::EMAT_RUN );
            video::Vector3D currentPosition = mNode.getPosition();
            auto direction = video::Vector3DCompatible(mTargetPosition - currentPosition).toIrrlichtVector();
            direction.Y = 0.0f;
            auto rotation = direction.getHorizontalAngle();
            mNode.setRotation(video::Vector3DCompatible(rotation));
        }
    }
}
