#include "NodeManager.h"
#include <ISceneManager.h>

namespace leviathan {
    namespace world {
        NodeManager::NodeManager(irr::scene::ISceneManager* sceneManager)
        : sceneManager_(sceneManager), node_(Node3D()) {}

        NodeManager::~NodeManager() {}

        INode3D& NodeManager::add3DNode(const char* fileName, video::Position3D position, video::Vector3D offset,
            video::Rotation3D rotation, video::Scale3D scale) {
            (void)fileName;
            (void)position;
            (void)offset;
            (void)rotation;
            (void)scale;
            return node_;
        }

        void NodeManager::unload() {}
    }
}
