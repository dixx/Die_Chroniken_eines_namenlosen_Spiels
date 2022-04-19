#include "Ground.h"
#include "NodeManager.h"
#include <video/Vector3D.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        Ground::Ground(NodeManager& nodeManager) : mNodeManager(nodeManager) {}

        void Ground::add(const Node3DConfiguration& tileConfig) {
            mNodeManager.addGroundTile(tileConfig);
        }

        Ground::~Ground() {
            unload();
        }

        void Ground::unload() {
            mNodeManager.unloadGround();
        }

        float Ground::getHeight(const video::Position3D& position) const {
            return mNodeManager.getWalkableHeight(position);
        }

        void Ground::adjustHeightOf(video::IPositionable& object) const {
            video::Position3D position = object.getPosition();
            position.y = getHeight(position);
            object.setPosition(position);
        }
    }
}
