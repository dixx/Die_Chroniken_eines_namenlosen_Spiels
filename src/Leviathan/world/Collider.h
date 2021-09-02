/*! \file Collider.h
 *  \brief Bietet Zugriff auf Kollisionserkennung.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_COLLIDER_H
#define LEVIATHAN_WORLD_COLLIDER_H

namespace irr {
    namespace scene {
        class ISceneCollisionManager;
        class ISceneManager;
        class ISceneNode;
    }
}

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;
    }

    namespace world {
        struct Collision;
        class NodeManager;

        /*! \class Collider Collider.h "Collider.h"
         *  \brief Bietet Zugriff auf Kollisionserkennung.
         */
        class Collider {
        public:
            explicit Collider(irr::scene::ISceneManager* sceneManager);

            Collision getCollision(irr::scene::ISceneNode* rootNode, const video::Position3D& position) const;

        private:
            irr::scene::ISceneManager* sceneManager_ = nullptr;
        };
    }
}

#endif
