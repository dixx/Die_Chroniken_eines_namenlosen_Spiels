/*! \file NodeManager.h
 *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODE_MANAGER_H
#define LEVIATHAN_WORLD_NODE_MANAGER_H

#include "Character.h"
#include "Collider.h"
#include "Decoration.h"
#include "GroundTile.h"
#include <list>
#include <memory>

namespace irr {
    namespace scene {
        class ISceneManager;
        class ISceneNode;
    }
}

namespace leviathan {
    namespace characters {
        struct CharacterConfiguration;
    }
    namespace video {
        class Textures;
        struct Vector3D;
        using Position3D = Vector3D;
    }

    namespace world {
        struct Node3DConfiguration;

        /*! \class NodeManager
         *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
         */
        class NodeManager final {
        public:
            /*! \brief Konstruktor mit Konfiguration.
             *  \param sceneManager: Szenen-Manager des initialisierten Irrlicht Device
             *  \param textures: Instanz der Texturenverwaltung
             */
            NodeManager(irr::scene::ISceneManager* sceneManager, video::Textures& textures);

            /*! \brief Destruktor.
             */
            ~NodeManager();

            NodeManager() = delete;
            NodeManager(const NodeManager&) = delete;
            NodeManager(NodeManager&&) = delete;
            NodeManager& operator=(const NodeManager&) = delete;
            NodeManager& operator=(NodeManager&&) = delete;

            Character& createHeroNode(const characters::CharacterConfiguration& characterConfig);

            void addGroundTile(const Node3DConfiguration& nodeConfig);

            void addDecoration(const Node3DConfiguration& nodeConfig);

            void unloadHeroes();

            void unloadGround();

            void unloadDecorations();

            float getWalkableHeight(const video::Vector3D& position) const;

        private:
            Collider mCollider;
            video::Textures& mTextures;
            irr::scene::ISceneManager* mSceneManager = nullptr;
            std::list<std::unique_ptr<Character>> mHeroNodes = std::list<std::unique_ptr<Character>>();
            std::list<std::unique_ptr<GroundTile>> mGroundNodes = std::list<std::unique_ptr<GroundTile>>();
            std::list<std::unique_ptr<Decoration>> mDecorativeNodes = std::list<std::unique_ptr<Decoration>>();
            irr::scene::ISceneNode* mWorldNode = nullptr;
            irr::scene::ISceneNode* mResponsiveNodesRootNode = nullptr;
            irr::scene::ISceneNode* mWalkableNodesRootNode = nullptr;
            irr::scene::ISceneNode* mDecorativeNodesRootNode = nullptr;

            void addNodeTree();
            void addNodeNames();
        };
    }
}

#endif
