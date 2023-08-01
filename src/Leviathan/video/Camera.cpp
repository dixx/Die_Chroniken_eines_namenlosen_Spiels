#include "Camera.h"
#include "../core/Configuration.h"
#include "Constants.h"
#include "ICameraSceneNode.h"
#include "ISceneManager.h"
#include "vector3d.h"
#include <stdexcept>

namespace leviathan {
    namespace video {
        Camera::Camera(irr::scene::ISceneManager* sceneManager, core::Configuration& config)
        : mCamera(sceneManager->addCameraSceneNode(0, mOffset.toIrrlichtVector())) {
            mCamera->setFarValue(config.getFarValue());
            mCamera->setNearValue(0.1f);
            mCamera->setFOV(1.f);
            mCamera->setAspectRatio(
                static_cast<float>(config.getScreenSize().w) / static_cast<float>(config.getScreenSize().h));
            mCamera->bindTargetAndRotation(true);
            mCamera->setInputReceiverEnabled(false);
        }

        void Camera::setTargetPosition(const Position3D& targetPosition) {
            mTargetPosition = targetPosition;
        }

        void Camera::setRotationSpeed(const float rotationSpeed) {
            mRotationSpeed = rotationSpeed;
        }

        void Camera::enableRotation(const bool isRotating) {
            mIsRotating = isRotating;
        }

        void Camera::setMovementSpeed(const Vector3D& movementSpeed) {
            mMovementSpeed = movementSpeed;
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

            mCamera->setPosition((mTargetPosition + mOffset).toIrrlichtVector());
            mCamera->updateAbsolutePosition();
            mCamera->setTarget(mTargetPosition.toIrrlichtVector());
        }

        Position3D Camera::getPosition() const {
            return mTargetPosition;
        }

        void Camera::setPosition(const Position3D& position) {
            setTargetPosition(position);
        }
    }
}
