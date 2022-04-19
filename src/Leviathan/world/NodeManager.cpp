#include "NodeManager.h"
#include "IMeshCache.h"
#include "ISceneManager.h"
#include "NodeUsageBitmasks.h"
#include <characters/CharacterConfiguration.h>
#include <video/Vector3D.h>
#include <world/Collision.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        NodeManager::NodeManager(irr::scene::ISceneManager* sceneManager)
        : mCollider(sceneManager), mSceneManager(sceneManager) {
            addNodeTree();
            addNodeNames();
        }

        NodeManager::~NodeManager() {
            unloadHeroes();
            unloadGround();
            mWorldNode->removeAll();
            mWorldNode->remove();
        }

        Character& NodeManager::createHeroNode(const characters::CharacterConfiguration& characterConfig) {
            mHeroNodes.emplace_back(std::make_unique<Character>(characterConfig, mSceneManager));
            return *(mHeroNodes.back());
        }

        void NodeManager::addGroundTile(const Node3DConfiguration& nodeConfig) {
            mGroundNodes.emplace_back(std::make_unique<GroundTile>(nodeConfig, mSceneManager));
        }

        void NodeManager::unloadHeroes() {
            mHeroNodes.clear();
            mSceneManager->getMeshCache()->clearUnusedMeshes();
        }

        void NodeManager::unloadGround() {
            mGroundNodes.clear();
            mWalkableNodes->removeAll();
            mSceneManager->getMeshCache()->clearUnusedMeshes();
        }

        float NodeManager::getWalkableHeight(const video::Position3D& position) const {
            return mCollider.getCollisionTopDown(mWalkableNodes, position).collisionPoint.y;
        }

        void NodeManager::addNodeTree() {
            mWorldNode = mSceneManager->addEmptySceneNode(0, ID_WORLD_ROOT);
            mResponsiveNodes = mSceneManager->addEmptySceneNode(mWorldNode, ID_RESPONSIVE_ROOT + NODE_FLAG_RESPONSIVE);
            mWalkableNodes = mSceneManager->addEmptySceneNode(
                mResponsiveNodes, ID_WALKABLE_ROOT + NODE_FLAG_WALKABLE + NODE_FLAG_RESPONSIVE);
        }

        void NodeManager::addNodeNames() {
            mWorldNode->setName("worldNode");
            mResponsiveNodes->setName("responsiveNodes");
            mWalkableNodes->setName("walkableNodes");
        }
    }
}
