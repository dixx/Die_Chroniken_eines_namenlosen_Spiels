/*! \file Decorations.h
 *  \brief Bietet Zugriff auf rein dekorative Elemente.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_DECORATIONS_H
#define LEVIATHAN_WORLD_DECORATIONS_H

#include <world/IDecorations.h>

namespace leviathan {
    namespace world {
        class NodeManager;
        struct Node3DConfiguration;

        class Decorations final : public IDecorations {
        public:
            explicit Decorations(NodeManager& nodeManager);

            ~Decorations();

            Decorations() = delete;
            Decorations(const Decorations&) = delete;
            Decorations(const Decorations&&) = delete;
            Decorations& operator=(const Decorations&) = delete;
            Decorations& operator=(const Decorations&&) = delete;

            void add(const Node3DConfiguration& tileConfig) override;

            void unload() override;

        private:
            NodeManager& mNodeManager;
        };
    }
}

#endif
