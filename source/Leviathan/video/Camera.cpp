#include "Camera.h"
#include "Constants.h"
#include <stdexcept>

namespace leviathan {
    namespace video {
        Camera::Camera(irr::IrrlichtDevice* graphicDevice)
        : camera_(graphicDevice->getSceneManager()->addCameraSceneNode()) {}

        Camera::Camera(irr::IrrlichtDevice* graphicDevice, leviathan::core::Configuration& config)
        : camera_(graphicDevice->getSceneManager()->addCameraSceneNode()) {
            camera_->setFarValue(config.getFarValue());
        }
    }
}
