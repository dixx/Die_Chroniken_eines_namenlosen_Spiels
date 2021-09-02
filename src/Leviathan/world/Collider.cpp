#include "Collider.h"
#include "Collision.h"
#include "ISceneCollisionManager.h"
#include "ISceneManager.h"
#include "ISceneNode.h"
#include "NodeManager.h"
#include "NodeUsageBitmasks.h"
#include "line3d.h"
#include "triangle3d.h"
#include "vector3d.h"

namespace leviathan {
    namespace world {
        Collider::Collider(irr::scene::ISceneManager* sceneManager) : sceneManager_(sceneManager) {}

        Collision Collider::getCollision(irr::scene::ISceneNode* rootNode, const video::Position3D& position) const {
            irr::core::line3df ray(
                position.x, position.y + 200.f, position.z, position.x, -200.f, position.z);  // TODO caluclate length
            irr::core::vector3df collisionPoint;
            irr::core::triangle3df collisionTriangle;
            irr::scene::ISceneNode* collisionNode =
                sceneManager_->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, collisionPoint,
                    collisionTriangle, BITMASK_WALKABLE,  // Nur Szenenknoten mit entsprechenden Flags werden geprüft
                    rootNode,  // Nur dieser Szenenknoten und alle darunterliegenden werden geprüft
                    true  // Debug-Objekte nicht behandeln
                );
            return {{collisionPoint.X, collisionPoint.Y, collisionPoint.Z}, collisionNode != 0};
        }
    }
}
