#include "NodeManager.h"
#include <IMeshCache.h>
#include <ISceneManager.h>

namespace leviathan {
    namespace world {
        NodeManager::NodeManager(irr::scene::ISceneManager* sceneManager) : sceneManager_(sceneManager) {}

        NodeManager::~NodeManager() {
            unloadGround();
        }

        // void NodeManager::addHeroNode(const Node3DConfiguration& nodeConfig) {
        //     (void)nodeConfig;
        //     heroNodes_.emplace_back(nodeConfig);
        //     return *(heroNodes_.back());
        // }

        void NodeManager::addGroundTile(const Node3DConfiguration& nodeConfig) {
            groundNodes_.emplace_back(std::make_unique<GroundTile>(nodeConfig, sceneManager_));
        }

        void NodeManager::unloadGround() {
            groundNodes_.clear();
            sceneManager_->getMeshCache()->clearUnusedMeshes();
        }
    }
}
