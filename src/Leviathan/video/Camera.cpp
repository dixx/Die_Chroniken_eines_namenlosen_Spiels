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
            camera_->setFOV(1.0f);
            camera_->setAspectRatio(
                static_cast<irr::f32>(config.getScreenSize().w) / static_cast<irr::f32>(config.getScreenSize().h));
            camera_->setInputReceiverEnabled(false);
        }

        void Camera::setTargetPosition(const Position3D& targetPosition) {
            targetPosition_ = targetPosition;
        }

        void Camera::setRotationSpeed(const float rotationSpeed) {
            rotationSpeed_ = rotationSpeed;
        }

        void Camera::enableRotation(const bool isRotating) {
            isRotating_ = isRotating;
        }

        void Camera::update(const float elapsedSeconds) {
            irr::core::vector3df targetPosition = targetPosition_.toIrrlichtVector();
            camera_->setTarget(targetPosition);
            if (isRotating_) {
                offset_.rotateXZBy(rotationSpeed_ * elapsedSeconds);
            }
            camera_->setPosition(targetPosition + offset_);
        }
    }
}
