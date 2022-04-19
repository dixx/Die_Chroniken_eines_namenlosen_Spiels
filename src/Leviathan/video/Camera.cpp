#include "Camera.h"
#include "../core/Configuration.h"
#include "Constants.h"
#include "ICameraSceneNode.h"
#include "ISceneManager.h"
#include "vector3d.h"
#include <stdexcept>

namespace leviathan {
    namespace video {
        Camera::Camera(irr::scene::ISceneManager* sceneManager, leviathan::core::Configuration& config)
        : mCamera(sceneManager->addCameraSceneNode(0, mOffset)) {
            mCamera->setFarValue(config.getFarValue());
            mCamera->setNearValue(0.1f);
            mCamera->setFOV(1.f);
            mCamera->setAspectRatio(
                static_cast<float>(config.getScreenSize().w) / static_cast<float>(config.getScreenSize().h));
            mCamera->bindTargetAndRotation(true);
            mCamera->setInputReceiverEnabled(false);
        }

        void Camera::setTargetPosition(const Position3D& targetPosition) {
            mTargetPosition.set(targetPosition.x, targetPosition.y, targetPosition.z);
        }

        void Camera::setRotationSpeed(const float rotationSpeed) {
            mRotationSpeed = rotationSpeed;
        }

        void Camera::enableRotation(const bool isRotating) {
            mIsRotating = isRotating;
        }

        void Camera::setMovementSpeed(const Vector3D& movementSpeed) {
            mMovementSpeed.set(movementSpeed.x, movementSpeed.y, movementSpeed.z);
        }

        void Camera::enableMovement(const bool isMoving) {
            mIsMoving = isMoving;
        }

        void Camera::update(const float elapsedSeconds) {
            if (mIsRotating) {
                float rotationDelta = mRotationSpeed * elapsedSeconds;
                mOffset.rotateXZBy(rotationDelta);
                mRotation += rotationDelta;
            }
            if (mIsMoving) {
                auto direction = mMovementSpeed * elapsedSeconds;
                direction.rotateXZBy(mRotation);
                mTargetPosition += direction;
            }

            mCamera->setPosition(mTargetPosition + mOffset);
            mCamera->updateAbsolutePosition();
            mCamera->setTarget(mTargetPosition);
        }

        Position3D Camera::getPosition() const {
            return Position3D({mTargetPosition.X, mTargetPosition.Y, mTargetPosition.Z});
        }

        void Camera::setPosition(const Position3D& position) {
            setTargetPosition(position);
        }
    }
}
