#include "../../src/Leviathan/world/Ground.h"
#include "../../src/Leviathan/video/Textures.h"
#include "../../src/Leviathan/world/NodeManager.h"
#include "../../src/Leviathan/world/NodeUsageBitmasks.h"
#include "../helpers/TestHelper.h"
#include "ISceneManager.h"
#include "ITexture.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <world/Node3DConfiguration.h>

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)

TEST_CASE("Ground", "[integration]") {
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile", 1.f /* radius, center is at 0,0,0 */);  // add a test mesh to avoid getting a nullptr
    irr::core::dimension2du size(1, 1);
    TestHelper::graphicEngine()->getVideoDriver()->addTexture(
        size, "path/to/textureFile");  // add a test texture to avoid getting a nullptr
    leviathan::world::Node3DConfiguration groundTileConfig({"path/to/meshFile", "path/to/textureFile"});
    Mock<irr::video::ITexture> textureMock;
    Mock<irr::video::IVideoDriver> videoDriverMock;
    When(OverloadedMethod(videoDriverMock, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
    Fake(Method(videoDriverMock, setTextureCreationFlag));
    leviathan::video::Textures textures(&videoDriverMock.get(), TestHelper::Logger());
    leviathan::world::NodeManager nodeManager(TestHelper::graphicEngine()->getSceneManager(), textures);
    leviathan::world::Ground subject(nodeManager);
    irr::scene::ISceneNode* walkables(
        TestHelper::graphicEngine()->getSceneManager()->getSceneNodeFromName("walkableNodes"));

    SECTION("add") {
        SECTION("single ground tile") {
            subject.add(groundTileConfig);
            irr::core::array<irr::scene::ISceneNode*> nodes;
            TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes);
            REQUIRE(nodes.size() == 1);
            REQUIRE(walkables->getChildren().size() == 1);
            REQUIRE((*(walkables->getChildren().begin()))->getID() == NODE_FLAG_WALKABLE + NODE_FLAG_RESPONSIVE);
            REQUIRE((*(walkables->getChildren().begin()))->getAbsolutePosition().X == Approx(0.f));
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
        REQUIRE(walkables->getChildren().empty());
    }

    SECTION("get height at Position") {
        subject.add(groundTileConfig);
        REQUIRE(subject.getHeight({0.f, 0.f, 0.f}) == Approx(1.f));
        REQUIRE(subject.getHeight({1.f, 2.f, 3.f}) == Approx(0.f));
    }
}
