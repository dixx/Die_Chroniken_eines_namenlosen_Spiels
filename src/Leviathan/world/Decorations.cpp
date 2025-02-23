#include "Decorations.h"
#include "NodeManager.h"
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        Decorations::Decorations(NodeManager& nodeManager) : mNodeManager(nodeManager) {}

        void Decorations::add(const Node3DConfiguration& nodeConfig) {
            mNodeManager.addDecoration(nodeConfig);
        }

        Decorations::~Decorations() {
            unload();
        }

        void Decorations::unload() {
            mNodeManager.unloadDecorations();
        }
    }
}
