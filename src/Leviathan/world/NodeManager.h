/*! \file NodeManager.h
 *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_NODE_MANAGER_H
#define LEVIATHAN_WORLD_NODE_MANAGER_H

#include "Node3D.h"
#include <world/INode3D.h>
#include <world/INodeManager.h>

namespace irr {
    namespace scene {
        class ISceneManager;
    }
}

namespace leviathan {
    namespace world {

        /*! \class NodeManager
         *  \brief Erstellt und verwaltet alle geometrischen Objekte und deren Attribute.
         */
        class NodeManager final : public INodeManager {
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
            NodeManager(const NodeManager&&) = delete;
            NodeManager& operator=(const NodeManager&) = delete;
            NodeManager& operator=(const NodeManager&&) = delete;

            INode3D& add3DNode(const char* fileName, video::Position3D position, video::Vector3D offset,
                video::Rotation3D rotation, video::Scale3D scale);

            void unload();

        private:
            irr::scene::ISceneManager* sceneManager_ = nullptr;
            Node3D node_;
        };
    }
}

#endif
