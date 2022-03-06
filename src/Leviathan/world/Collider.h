/*! \file Collider.h
 *  \brief Bietet Zugriff auf Kollisionserkennung.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_COLLIDER_H
#define LEVIATHAN_WORLD_COLLIDER_H

#include <world/ICollider.h>

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
        class Collider final : public ICollider {
        public:
            explicit Collider(irr::scene::ISceneManager* sceneManager);

            Collider() = delete;
            Collider(const Collider&) = delete;
            Collider(const Collider&&) = delete;
            Collider& operator=(const Collider&) = delete;
            Collider& operator=(const Collider&&) = delete;

            Collision getCollisionTopDown(irr::scene::ISceneNode* rootNode, const video::Position3D& position,
                const float heightOffset = 200.f) const;

            Collision getCollisionFromScreenCoordinates(const video::Position2D& screenCoordinates) const;

        private:
            irr::scene::ISceneManager* sceneManager_ = nullptr;
        };
    }
}

#endif
