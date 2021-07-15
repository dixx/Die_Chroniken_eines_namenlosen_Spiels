/*! \file NodeManager.h
 *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODE_MANAGER_H
#define LEVIATHAN_WORLD_NODE_MANAGER_H

#include "Character.h"
#include "GroundTile.h"
#include <list>
#include <memory>
#include <world/INode3D.h>

namespace irr {
    namespace scene {
        class ISceneManager;
    }
}

namespace leviathan {
    namespace characters {
        struct CharacterConfiguration;
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

            Character& addHeroNode(const characters::CharacterConfiguration& characterConfig);

            void addGroundTile(const Node3DConfiguration& nodeConfig);

            void unloadHeroes();

            void unloadGround();

        private:
            irr::scene::ISceneManager* sceneManager_ = nullptr;
            std::list<std::unique_ptr<Character>> heroNodes_ = std::list<std::unique_ptr<Character>>();
            std::list<std::unique_ptr<GroundTile>> groundNodes_ = std::list<std::unique_ptr<GroundTile>>();
        };
    }
}

#endif
