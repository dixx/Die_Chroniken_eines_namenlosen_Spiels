#include "NodeManager.h"
#include "Collision.h"
#include "IMeshCache.h"
#include "ISceneManager.h"
#include "NodeUsageBitmasks.h"
#include <characters/CharacterConfiguration.h>
#include <video/Vector3D.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        NodeManager::NodeManager(irr::scene::ISceneManager* sceneManager)
        : collider_(sceneManager), sceneManager_(sceneManager) {
            addNodeTree();
            addNodeNames();
        }

        NodeManager::~NodeManager() {
            unloadHeroes();
            unloadGround();
            worldNode_->removeAll();
            worldNode_->remove();
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
            walkableNodes_->removeAll();
            sceneManager_->getMeshCache()->clearUnusedMeshes();
        }

        float NodeManager::getWalkableHeight(const video::Position3D& position) const {
            return collider_.getCollision(walkableNodes_, position).collisionPoint.y;
        }

        void NodeManager::addNodeTree() {
            worldNode_ = sceneManager_->addEmptySceneNode(0, ID_WORLD_ROOT);
            responsiveNodes_ = sceneManager_->addEmptySceneNode(worldNode_, ID_RESPONSIVE_ROOT + NODE_FLAG_RESPONSIVE);
            walkableNodes_ = sceneManager_->addEmptySceneNode(
                responsiveNodes_, ID_WALKABLE_ROOT + NODE_FLAG_WALKABLE + NODE_FLAG_RESPONSIVE);
        }

        void NodeManager::addNodeNames() {
            worldNode_->setName("worldNode");
            responsiveNodes_->setName("responsiveNodes");
            walkableNodes_->setName("walkableNodes");
        }
    }
}
