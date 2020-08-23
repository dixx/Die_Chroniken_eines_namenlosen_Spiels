#include "Camera.h"
#include "Constants.h"
#include <stdexcept>

namespace leviathan {
    namespace video {
        Camera::Camera(irr::scene::ISceneManager* sceneManager, leviathan::core::Configuration& config)
        : camera_(sceneManager->addCameraSceneNode()) {
            camera_->setFarValue(config.getFarValue());
        }
    }
}
