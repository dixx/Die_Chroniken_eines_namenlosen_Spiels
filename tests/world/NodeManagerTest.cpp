#include "../../src/Leviathan/world/NodeManager.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <world/INode3D.h>

using namespace fakeit;

TEST_CASE("NodeManager", "[integration]") {
    leviathan::world::Node3DConfiguration tileConfig(
        {"path/to/meshFile", {1.f, 2.f, 3.f}, {11.f, 22.f, 33.f}, {0.f, 0.f, 0.f}, {2.f, 3.f, 4.f}});
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile", 1.f /* radius, center is at 0,0,0 */);  // add a test mesh to avoid getting a nullptr
    leviathan::world::NodeManager subject(TestHelper::graphicEngine()->getSceneManager());

    SECTION("add ground tiles objects") {
        subject.addGroundTile(tileConfig);
        auto irrlichtNode = TestHelper::graphicEngine()->getSceneManager()->getSceneNodeFromType(irr::scene::ESNT_MESH);
        REQUIRE(irrlichtNode != nullptr);

        SECTION("objects are initialized with given parameters") {
            REQUIRE(irrlichtNode->getPosition().X == Approx(1.f));
            REQUIRE(irrlichtNode->getPosition().Y == Approx(2.f));
            REQUIRE(irrlichtNode->getPosition().Z == Approx(3.f));
            REQUIRE(irrlichtNode->getBoundingBox().MinEdge.X == Approx(11.f - 2.f));
            REQUIRE(irrlichtNode->getBoundingBox().MinEdge.Y == Approx(22.f - 3.f));
            REQUIRE(irrlichtNode->getBoundingBox().MinEdge.Z == Approx(33.f - 4.f));
            REQUIRE(irrlichtNode->getBoundingBox().MaxEdge.X == Approx(11.f + 2.f));
            REQUIRE(irrlichtNode->getBoundingBox().MaxEdge.Y == Approx(22.f + 3.f));
            REQUIRE(irrlichtNode->getBoundingBox().MaxEdge.Z == Approx(33.f + 4.f));
            // honestly, I'm too lazy for the rotation calculations. I'll add one if there are bugs.
        }

        SECTION("objects are unique") {
            subject.addGroundTile(tileConfig);
            irr::core::array<irr::scene::ISceneNode*> nodes;
            TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes);
            REQUIRE(nodes.size() == 2);
            REQUIRE(nodes[1] != nodes[0]);
        }
    }

    SECTION("unload all ground tiles") {
        subject.addGroundTile(tileConfig);
        subject.unloadGround();
        irr::core::array<irr::scene::ISceneNode*> nodes;
        TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes);
        REQUIRE(nodes.empty());
    }
}
