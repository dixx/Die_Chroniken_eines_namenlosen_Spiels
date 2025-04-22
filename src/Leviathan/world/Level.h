/*! \file Level.h
 *  \brief Bietet Zugriff auf die Repräsentation eines Levels.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_LEVEL_H
#define LEVIATHAN_WORLD_LEVEL_H

#include "yaml-cpp/yaml.h"
#include <world/ILevel.h>

namespace leviathan {
    namespace world {
        class NodeManager;
        struct Node3DConfiguration;

        class Level final : public ILevel {
        public:
            explicit Level(NodeManager& nodeManager);

            ~Level() = default;

            Level() = delete;
            Level(const Level&) = delete;
            Level(const Level&&) = delete;
            Level& operator=(const Level&) = delete;
            Level& operator=(const Level&&) = delete;

            void loadFromFile(const char* fileName) override;

        private:
            NodeManager& mNodeManager;

            void loadGroundTiles(YAML::Node& content);
        };
    }
}

#endif
