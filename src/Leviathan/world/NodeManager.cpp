#include "NodeManager.h"
#include <IMeshCache.h>
#include <ISceneManager.h>
#include <characters/CharacterConfiguration.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        NodeManager::NodeManager(irr::scene::ISceneManager* sceneManager) : sceneManager_(sceneManager) {}

        NodeManager::~NodeManager() {
            unloadHeroes();
            unloadGround();
        }

        Character& NodeManager::createHeroNode(const characters::CharacterConfiguration& characterConfig) {
            heroNodes_.emplace_back(std::make_unique<Character>(characterConfig, sceneManager_));
            return *(heroNodes_.back());
        }

        void NodeManager::addGroundTile(const Node3DConfiguration& nodeConfig) {
            groundNodes_.emplace_back(std::make_unique<GroundTile>(nodeConfig, sceneManager_));
        }

        void NodeManager::unloadHeroes() {
            heroNodes_.clear();
            sceneManager_->getMeshCache()->clearUnusedMeshes();
        }

        void NodeManager::unloadGround() {
            groundNodes_.clear();
            sceneManager_->getMeshCache()->clearUnusedMeshes();
        }
    }
}
