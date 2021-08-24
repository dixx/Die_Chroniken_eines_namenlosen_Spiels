#include "Ground.h"
#include "NodeManager.h"
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
    }
}
