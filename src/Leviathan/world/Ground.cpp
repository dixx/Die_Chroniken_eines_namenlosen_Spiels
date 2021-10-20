#include "Ground.h"
#include "NodeManager.h"
#include <video/Vector3D.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        Ground::Ground(NodeManager& nodeManager) : nodeManager_(nodeManager) {}

        void Ground::add(const Node3DConfiguration& tileConfig) {
            nodeManager_.addGroundTile(tileConfig);
        }

        Ground::~Ground() {
            unload();
        }

        void Ground::unload() {
            nodeManager_.unloadGround();
        }

        float Ground::getHeight(const video::Position3D& position) const {
            return nodeManager_.getWalkableHeight(position);
        }

        void Ground::adjustHeight(video::IPositionable& object) const {
            video::Position3D position = object.getPosition();
            position.y = getHeight(position);
            object.setPosition(position);
        }
    }
}
