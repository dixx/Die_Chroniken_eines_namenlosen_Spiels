/*! \file Ground.h
 *  \brief Bietet Zugriff auf begehbaren Boden.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_GROUND_H
#define LEVIATHAN_WORLD_GROUND_H

#include <world/IGround.h>

namespace leviathan {
    namespace video {
        struct Vector3D;
        using Position3D = Vector3D;
    }

    namespace world {
        class NodeManager;
        struct Node3DConfiguration;

        class Ground final : public IGround {
        public:
            explicit Ground(NodeManager& nodeManager);

            ~Ground();

            Ground() = delete;
            Ground(const Ground&) = delete;
            Ground(const Ground&&) = delete;
            Ground& operator=(const Ground&) = delete;
            Ground& operator=(const Ground&&) = delete;

            void add(const Node3DConfiguration& tileConfig) override;

            void unload() override;

            float getHeight(const video::Position3D& position) const override;

            void adjustHeightOf(video::IPositionable& object) const override;

        private:
            NodeManager& nodeManager_;
        };
    }
}

#endif
