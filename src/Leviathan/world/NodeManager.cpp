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
        NodeManager::NodeManager(irr::scene::ISceneManager* sceneManager, video::Textures& textures)
        : mCollider(sceneManager), mTextures(textures), mSceneManager(sceneManager) {
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
            mHeroNodes.emplace_back(std::make_unique<Character>(characterConfig, mTextures, mSceneManager));
            return *(mHeroNodes.back());
        }

        void NodeManager::addGroundTile(const Node3DConfiguration& nodeConfig) {
            mGroundNodes.emplace_back(std::make_unique<GroundTile>(nodeConfig, mTextures, mSceneManager));
        }

        void NodeManager::addDecoration(const Node3DConfiguration& nodeConfig) {
            mDecorativeNodes.emplace_back(std::make_unique<Decoration>(nodeConfig, mTextures, mSceneManager));
        }

        void NodeManager::unloadHeroes() {
            mHeroNodes.clear();
            mSceneManager->getMeshCache()->clearUnusedMeshes();
        }

        void NodeManager::unloadGround() {
            mGroundNodes.clear();
            mWalkableNodesRootNode->removeAll();
            mSceneManager->getMeshCache()->clearUnusedMeshes();
        }

        void NodeManager::unloadDecorations() {
            mDecorativeNodes.clear();
            mDecorativeNodesRootNode->removeAll();
            mSceneManager->getMeshCache()->clearUnusedMeshes();
        }

        float NodeManager::getWalkableHeight(const video::Position3D& position) const {
            return mCollider.getCollisionTopDown(mWalkableNodesRootNode, position).collisionPoint.y;
        }

        void NodeManager::addNodeTree() {
            mWorldNode = mSceneManager->addEmptySceneNode(0, ID_WORLD_ROOT);
            mResponsiveNodesRootNode = mSceneManager->addEmptySceneNode(
                mWorldNode, ID_RESPONSIVE_ROOT + NODE_FLAG_RESPONSIVE);
            mWalkableNodesRootNode = mSceneManager->addEmptySceneNode(
                mResponsiveNodesRootNode, ID_WALKABLE_ROOT + NODE_FLAG_WALKABLE + NODE_FLAG_RESPONSIVE);
            mDecorativeNodesRootNode = mSceneManager->addEmptySceneNode(mWorldNode);
        }

        void NodeManager::addNodeNames() {
            mWorldNode->setName("worldNode");
            mResponsiveNodesRootNode->setName("responsiveNodes");
            mWalkableNodesRootNode->setName("walkableNodes");
            mDecorativeNodesRootNode->setName("decorativeNodes");
        }
    }
}
