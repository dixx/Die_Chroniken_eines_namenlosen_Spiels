/*! \file NodeManager.h
 *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODE_MANAGER_H
#define LEVIATHAN_WORLD_NODE_MANAGER_H

#include "Character.h"
#include "Collider.h"
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
        struct Vector3D;
        using Position3D = Vector3D;
    }

    namespace world {
        class Node3DConfiguration;

        /*! \class NodeManager
         *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
         */
        class NodeManager final {
        public:
            /*! \brief Konstruktor mit Konfiguration.
             *  \param sceneManager: Szenen-Manager des initialisierten Irrlicht Device
             */
            explicit NodeManager(irr::scene::ISceneManager* sceneManager);

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

            void unloadHeroes();

            void unloadGround();

            float getWalkableHeight(const video::Vector3D& position) const;

        private:
            Collider collider_;
            irr::scene::ISceneManager* sceneManager_ = nullptr;
            std::list<std::unique_ptr<Character>> heroNodes_ = std::list<std::unique_ptr<Character>>();
            std::list<std::unique_ptr<GroundTile>> groundNodes_ = std::list<std::unique_ptr<GroundTile>>();
            irr::scene::ISceneNode* worldNode_ = nullptr;
            irr::scene::ISceneNode* responsiveNodes_ = nullptr;
            irr::scene::ISceneNode* walkableNodes_ = nullptr;

            void addNodeTree();
            void addNodeNames();
        };
    }
}

#endif
