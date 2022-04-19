#include "Collider.h"
#include "ISceneCollisionManager.h"
#include "ISceneManager.h"
#include "ISceneNode.h"
#include "NodeManager.h"
#include "NodeUsageBitmasks.h"
#include "line3d.h"
#include "triangle3d.h"
#include "vector3d.h"
#include <video/Position2D.h>
#include <world/Collision.h>

namespace leviathan {
    namespace world {
        Collider::Collider(irr::scene::ISceneManager* sceneManager) : mSceneManager(sceneManager) {}

        Collision Collider::getCollisionTopDown(
            irr::scene::ISceneNode* rootNode, const video::Position3D& position, const float heightOffset) const {
            irr::core::line3df ray(position.x, position.y + heightOffset, position.z, position.x,
                position.y - heightOffset, position.z);  // TODO caluclate length
            irr::core::vector3df collisionPoint;
            irr::core::triangle3df collisionTriangle;
            irr::scene::ISceneNode* collisionNode =
                mSceneManager->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(ray, collisionPoint,
                    collisionTriangle, BITMASK_WALKABLE,  // Nur Szenenknoten mit entsprechenden Flags werden geprüft
                    rootNode,  // Nur dieser Szenenknoten und alle darunterliegenden werden geprüft
                    true  // Debug-Objekte nicht behandeln
                );
            return {{collisionPoint.X, collisionPoint.Y, collisionPoint.Z}, collisionNode != 0};
        }

        Collision Collider::getCollisionFromScreenCoordinates(const video::Position2D& screenCoordinates) const {
            irr::core::line3df ray = mSceneManager->getSceneCollisionManager()->getRayFromScreenCoordinates(
                irr::core::position2di(screenCoordinates.x, screenCoordinates.y), mSceneManager->getActiveCamera());
            irr::core::vector3df collisionPoint;
            irr::core::triangle3df collisionTriangle;
            irr::scene::ISceneNode* collisionNode =
                mSceneManager->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
                    ray, collisionPoint, collisionTriangle,
                    NODE_FLAG_RESPONSIVE,  // Nur Szenenknoten mit entsprechenden Flags werden geprüft
                    mSceneManager->getSceneNodeFromName(
                        "responsiveNodes"),  // Nur dieser Szenenknoten und alle darunterliegenden werden geprüft
                    true  // Debug-Objekte nicht behandeln
                );

            return {{collisionPoint.X, collisionPoint.Y, collisionPoint.Z}, collisionNode != 0};
        }
    }
}
