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
        : camera_(sceneManager->addCameraSceneNode(0, offset_)) {
            camera_->setFarValue(config.getFarValue());
            camera_->setNearValue(0.1f);
            camera_->setFOV(1.f);
            camera_->setAspectRatio(
                static_cast<float>(config.getScreenSize().w) / static_cast<float>(config.getScreenSize().h));
            camera_->bindTargetAndRotation(true);
            camera_->setInputReceiverEnabled(false);
        }

        void Camera::setTargetPosition(const Position3D& targetPosition) {
            targetPosition_.set(targetPosition.x, targetPosition.y, targetPosition.z);
        }

        void Camera::setRotationSpeed(const float rotationSpeed) {
            rotationSpeed_ = rotationSpeed;
        }

        void Camera::enableRotation(const bool isRotating) {
            isRotating_ = isRotating;
        }

        void Camera::setMovementSpeed(const Vector3D& movementSpeed) {
            movementSpeed_.set(movementSpeed.x, movementSpeed.y, movementSpeed.z);
        }

        void Camera::enableMovement(const bool isMoving) {
            isMoving_ = isMoving;
        }

        void Camera::update(const float elapsedSeconds) {
            if (isRotating_) {
                float rotationDelta = rotationSpeed_ * elapsedSeconds;
                offset_.rotateXZBy(rotationDelta);
                rotation_ += rotationDelta;
            }
            if (isMoving_) {
                auto direction = movementSpeed_ * elapsedSeconds;
                direction.rotateXZBy(rotation_);
                targetPosition_ += direction;
            }

            camera_->setPosition(targetPosition_ + offset_);
            camera_->updateAbsolutePosition();
            camera_->setTarget(targetPosition_);
        }

        Position3D Camera::getPosition() const {
            return Position3D({targetPosition_.X, targetPosition_.Y, targetPosition_.Z});
        }

        void Camera::setPosition(const Position3D& position) {
            setTargetPosition(position);
        }
    }
}
