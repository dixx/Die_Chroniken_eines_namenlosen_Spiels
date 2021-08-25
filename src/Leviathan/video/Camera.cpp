#include "Camera.h"
#include "../core/Configuration.h"
#include "Constants.h"
#include "ICameraSceneNode.h"
#include "ISceneManager.h"
#include <stdexcept>

namespace leviathan {
    namespace video {
        Camera::Camera(irr::scene::ISceneManager* sceneManager, leviathan::core::Configuration& config)
        : camera_(sceneManager->addCameraSceneNode(0, irr::core::vector3df(90.f, 3.f, 0.f), irr::core::vector3df())) {
            camera_->setFarValue(config.getFarValue());
        }
    }
}
