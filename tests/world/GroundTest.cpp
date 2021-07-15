#include "../../src/Leviathan/world/Ground.h"
#include "../../src/Leviathan/world/NodeManager.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"
#include <world/Node3DConfiguration.h>

using namespace fakeit;

#define getMeshArgs irr::scene::IAnimatedMesh*(const irr::io::path&)

TEST_CASE("Ground", "[integration]") {
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile");  // add a test mesh to avoid getting a nullptr
    irr::core::dimension2du size(1, 1);
    TestHelper::graphicEngine()->getVideoDriver()->addTexture(
        size, "path/to/textureFile");  // add a test texture to avoid getting a nullptr
    leviathan::world::Node3DConfiguration groundTileConfig({"path/to/meshFile", "path/to/textureFile", {}, {}, {}});
    leviathan::world::NodeManager nodeManager(TestHelper::graphicEngine()->getSceneManager());
    leviathan::world::Ground subject(nodeManager);

    SECTION("add") {
        SECTION("single ground tile") {
            subject.add(groundTileConfig);
            irr::core::array<irr::scene::ISceneNode*> nodes;
            TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes);
            REQUIRE(nodes.size() == 1);
        }

        SECTION("multiple ground tiles") {
            subject.add(groundTileConfig);
            subject.add(groundTileConfig);
            irr::core::array<irr::scene::ISceneNode*> nodes;
            TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes);
            REQUIRE(nodes.size() == 2);
        }
    }

    SECTION("unload all ground tiles") {
        subject.add(groundTileConfig);
        subject.add(groundTileConfig);
        subject.unload();
        auto irrlichtNode = TestHelper::graphicEngine()->getSceneManager()->getSceneNodeFromType(irr::scene::ESNT_MESH);
        REQUIRE(irrlichtNode == nullptr);
    }
}
