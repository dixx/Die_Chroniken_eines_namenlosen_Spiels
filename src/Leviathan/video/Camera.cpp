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
        : camera_(sceneManager->addCameraSceneNode(0, offset_.toIrrlichtVector(), irr::core::vector3df())) {
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

        void Camera::setOffset(const Vector3D& offset) {
            offset_ = offset;
        }

        void Camera::update() {
            camera_->setTarget(targetPosition_.toIrrlichtVector());
            camera_->setPosition(targetPosition_.toIrrlichtVector() + offset_.toIrrlichtVector());
        }
    }
}
