/*! \file Level.h
 *  \brief Bietet Zugriff auf die Repräsentation eines Levels.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_WORLD_LEVEL_H
#define LEVIATHAN_WORLD_LEVEL_H

#include "yaml-cpp/yaml.h"
#include <video/Vector3D.h>
#include <world/ILevel.h>

namespace leviathan {
    namespace world {
        class NodeManager;
        class Ground;
        struct Node3DConfiguration;

        class Level final : public ILevel {
        public:
            Level(NodeManager& nodeManager, Ground& ground);

            ~Level() = default;

            Level() = delete;
            Level(const Level&) = delete;
            Level(const Level&&) = delete;
            Level& operator=(const Level&) = delete;
            Level& operator=(const Level&&) = delete;

            void loadFromFile(const char* fileName) override;

            const leviathan::video::Position3D& getSpawnPosition() const override;

        private:
            NodeManager& mNodeManager;
            Ground& mGround;
            leviathan::video::Position3D mSpawnPosition;

            void loadGroundTiles(YAML::Node& content);
            void loadSpawnPosition(YAML::Node& content);
        };
    }
}

#endif
