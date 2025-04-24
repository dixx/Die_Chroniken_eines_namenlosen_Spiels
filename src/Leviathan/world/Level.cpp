#include "Level.h"
#include "NodeManager.h"
#include <world/Ground.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        Level::Level(NodeManager& nodeManager, Ground& ground)
        : mNodeManager(nodeManager), mGround(ground), mSpawnPosition() {}

        void Level::loadFromFile(const char* fileName) {
            YAML::Node content;
            try {
                content = YAML::LoadFile(fileName);
            } catch (const YAML::BadFile& e) {
            } catch (const YAML::ParserException& e) {
            }
            if (!content) content = YAML::Load("---");

            loadGroundTiles(content);
            loadSpawnPosition(content);
            // load objects
        }

        const leviathan::video::Position3D& Level::getSpawnPosition() const {
            return mSpawnPosition;
        }

        void Level::loadGroundTiles(YAML::Node& content) {
            if (!content["map"]) return;
            if (!content["map"].IsSequence()) return;

            for (YAML::Node tile : content["map"]) {
                Node3DConfiguration tileConfig;

                if (tile["model"]) tileConfig.meshFileName = tile["model"].as<std::string>(tileConfig.meshFileName);
                if (tile["texture"])
                    tileConfig.textureFileName = tile["texture"].as<std::string>(tileConfig.textureFileName);
                if (tile["scale"]) {
                    if (tile["scale"].IsSequence() && tile["scale"].size() == 3) {
                        tileConfig.scale = {tile["scale"][0].as<float>(tileConfig.scale.x),
                            tile["scale"][1].as<float>(tileConfig.scale.y),
                            tile["scale"][2].as<float>(tileConfig.scale.z)};
                    } else if (tile["scale"].IsScalar()) {
                        float scale = tile["scale"].as<float>(tileConfig.scale.x);
                        tileConfig.scale = {scale, scale, scale};
                    }
                }

                mGround.add(tileConfig);
            }
        }

        void Level::loadSpawnPosition(YAML::Node& content) {
            if (!content["hero"] || !content["hero"].IsMap() || !content["hero"]["position"]) return;

            auto values = content["hero"]["position"];
            if (!values.IsSequence() || values.size() != 2) return;

            mSpawnPosition.x = values.as<float>(mSpawnPosition.x);
            mSpawnPosition.z = values.as<float>(mSpawnPosition.z);
            mSpawnPosition.y = mGround.getHeight({mSpawnPosition.x, 0.f, mSpawnPosition.z});
        }
    }
}
