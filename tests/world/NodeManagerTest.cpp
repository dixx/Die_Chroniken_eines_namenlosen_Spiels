#include "../../src/Leviathan/world/NodeManager.h"
#include "../../src/Leviathan/video/Textures.h"
#include "../helpers/TestHelper.h"
#include "ISceneManager.h"
#include "ITexture.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <characters/CharacterConfiguration.h>
#include <world/INode3D.h>

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)

TEST_CASE("NodeManager", "[integration]") {
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile", 1.f /* radius, center is at 0,0,0 */);  // add a test mesh to avoid getting a nullptr
    irr::core::dimension2du size(1, 1);
    TestHelper::graphicEngine()->getVideoDriver()->addTexture(
        size, "path/to/textureFile");  // add a test texture to avoid getting a nullptr
    leviathan::characters::CharacterConfiguration heroConfig({"name", "internal name",
        {"path/to/meshFile", "path/to/textureFile", {1.f, 2.f, 3.f}, {11.f, 22.f, 33.f}, {0.f, 0.f, 0.f},
            {0.f, 0.f, 0.f}, {2.f, 3.f, 4.f}}});
    leviathan::world::Node3DConfiguration tileConfig({"path/to/meshFile", "path/to/textureFile", {1.f, 2.f, 3.f},
        {11.f, 22.f, 33.f}, {0.f, 0.f, 0.f}, {0.f, 0.f, 0.f}, {2.f, 3.f, 4.f}});
    Mock<irr::video::ITexture> textureMock;
    Mock<irr::video::IVideoDriver> videoDriverMock;
    When(OverloadedMethod(videoDriverMock, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
    Fake(Method(videoDriverMock, setTextureCreationFlag));
    leviathan::video::Textures textures(&videoDriverMock.get(), TestHelper::Logger());
    leviathan::world::NodeManager subject(TestHelper::graphicEngine()->getSceneManager(), textures);

    SECTION("add hero objects") {
        subject.createHeroNode(heroConfig);
        auto irrlichtNode = TestHelper::graphicEngine()->getSceneManager()->getSceneNodeFromType(
            irr::scene::ESNT_ANIMATED_MESH);
        REQUIRE(irrlichtNode != nullptr);

        SECTION("objects are initialized with given parameters") {
            REQUIRE(irrlichtNode->getPosition().X == Approx(12.f));
            REQUIRE(irrlichtNode->getPosition().Y == Approx(24.f));
            REQUIRE(irrlichtNode->getPosition().Z == Approx(36.f));
            REQUIRE(irrlichtNode->getTransformedBoundingBox().MinEdge.X == Approx((1.f + 11.f) - (1.f * 2.f)));
            REQUIRE(irrlichtNode->getTransformedBoundingBox().MinEdge.Y == Approx((2.f + 22.f) - (1.f * 3.f)));
            REQUIRE(irrlichtNode->getTransformedBoundingBox().MinEdge.Z == Approx((3.f + 33.f) - (1.f * 4.f)));
            REQUIRE(irrlichtNode->getTransformedBoundingBox().MaxEdge.X == Approx((1.f + 11.f) + (1.f * 2.f)));
            REQUIRE(irrlichtNode->getTransformedBoundingBox().MaxEdge.Y == Approx((2.f + 22.f) + (1.f * 3.f)));
            REQUIRE(irrlichtNode->getTransformedBoundingBox().MaxEdge.Z == Approx((3.f + 33.f) + (1.f * 4.f)));
            // honestly, I'm too lazy for the rotation calculations. I'll add one if there are bugs.
        }

        SECTION("objects are unique") {
            subject.createHeroNode(heroConfig);
            irr::core::array<irr::scene::ISceneNode*> nodes;
            TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(
                irr::scene::ESNT_ANIMATED_MESH, nodes);
            REQUIRE(nodes.size() == 2);
            REQUIRE(nodes[1] != nodes[0]);
        }
    }

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

    SECTION("unload all heroes") {
        subject.createHeroNode(heroConfig);
        subject.unloadHeroes();
        irr::core::array<irr::scene::ISceneNode*> nodes;
        TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_ANIMATED_MESH, nodes);
        REQUIRE(nodes.empty());
    }

    SECTION("unload all ground tiles") {
        subject.addGroundTile(tileConfig);
        subject.unloadGround();
        irr::core::array<irr::scene::ISceneNode*> nodes;
        TestHelper::graphicEngine()->getSceneManager()->getSceneNodesFromType(irr::scene::ESNT_MESH, nodes);
        REQUIRE(nodes.empty());
    }
}
