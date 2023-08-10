#include "HeroMover.h"
#include <gui/IMousePointerControl.h>
#include <input/Action.h>
#include <input/IActions.h>
#include <video/Position2D.h>
#include <world/Collision.h>
#include <world/ICollider.h>
#include <world/IGround.h>

HeroMover::HeroMover(leviathan::ILeviathanDevice& gameEngine)
: mActions(gameEngine.Actions()), mCollider(gameEngine.Collider()), mGround(gameEngine.Ground()),
  mMousePointer(gameEngine.MousePointerControl()) {}

HeroMover::~HeroMover() {
    ignoreInput();
}

void HeroMover::onAction(const leviathan::input::Action action) {
    if (action.id == TARGET_SELECTED) {
        if (action.isActive) {
            // action started
            mIsActionOngoing = true;
            mIsMoving = true;
        } else {
            // action ended
            mIsActionOngoing = false;
        }
    }
}

void HeroMover::update(const float elapsedSeconds, const leviathan::video::Position3D& currentPosition) {
    mPosition = currentPosition;
    if (!mIsMoving) return;

    if (mIsActionOngoing) {
        leviathan::world::Collision collision = mCollider.getCollisionFromScreenCoordinates(
            mMousePointer.getPosition());
        if (collision.happened) {
            mTargetPosition = collision.collisionPoint;
        }
    }

    auto distanceLeft = mTargetPosition - currentPosition;
    if (distanceLeft.equals({0.0f, 0.0f, 0.0f}, 0.3f)) {
        // cease movement
        mIsMoving = false;
        mTargetPosition = currentPosition;
    } else {
        // move
        distanceLeft.setLength(mLocomotionSpeed * elapsedSeconds);
        mPosition = currentPosition + distanceLeft;
        mPosition.y = mGround.getHeight(mPosition);
        distanceLeft.y = 0.0f;  // Hero should not lean away from the target
        mRotation = distanceLeft.getHorizontalAngle();
    }
}

leviathan::video::Vector3D HeroMover::getPosition() const {
    return mPosition;
}

leviathan::video::Rotation3D HeroMover::getRotation() const {
    return mRotation;
}

bool HeroMover::isMoving() const {
    return mIsMoving;
}

void HeroMover::ignoreInput() {
    mActions.unsubscribe(*this, TARGET_SELECTED);
}

void HeroMover::reactToInput() {
    mActions.subscribe(*this, TARGET_SELECTED);
}
