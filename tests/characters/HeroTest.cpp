#include "../../src/Leviathan/characters/Hero.h"
#include "../../src/Leviathan/world/NodeManager.h"
#include "../helpers/CatchPatches.hpp"
#include "../helpers/OverloadedOperators.hpp"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include <characters/CharacterConfiguration.h>
#include <string>
#include <video/Vector3D.h>

TEST_CASE("Hero", "[integration]") {
    auto name = std::to_string(TestHelper::getUniqueId()).c_str();
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile");  // add a test mesh to avoid getting a nullptr
    irr::core::dimension2du size(1, 1);
    TestHelper::graphicEngine()->getVideoDriver()->addTexture(
        size, "path/to/textureFile");  // add a test texture to avoid getting a nullptr
    leviathan::characters::CharacterConfiguration heroConfig(
        {"name", name, {"path/to/meshFile", "path/to/textureFile", {}, {}, {}, {}}});
    leviathan::world::NodeManager nodeManager(TestHelper::graphicEngine()->getSceneManager());
    leviathan::characters::Hero subject(heroConfig, nodeManager);
    auto sceneNode = TestHelper::graphicEngine()->getSceneManager()->getSceneNodeFromName(name);

    SECTION("has a scene node") {
        REQUIRE(sceneNode != nullptr);
    }
    SECTION("has an internal name") {
        REQUIRE(subject.getInternalName() == name);
    }
    SECTION("has 3D attributes") {
        REQUIRE(subject.getPosition() == leviathan::video::Position3D({0.0f, 0.0f, 0.0f}));
        REQUIRE(subject.getRotation() == leviathan::video::Rotation3D({0.0f, 0.0f, 0.0f}));

        SECTION("which can be changed") {
            subject.setPosition({1.0f, 2.0f, 3.0f});
            subject.setRotation({4.0f, 5.0f, 6.0f});
            REQUIRE(subject.getPosition() == leviathan::video::Position3D({1.0f, 2.0f, 3.0f}));
            REQUIRE(subject.getRotation() == leviathan::video::Rotation3D({4.0f, 5.0f, 6.0f}));
        }
    }
    SECTION("is not visible after creation") {
        REQUIRE_FALSE(sceneNode->isVisible());
    }
    SECTION("in-game figurine can be enabled or disabled") {
        subject.enablePlayableCharacter();
        REQUIRE(sceneNode->isVisible());
        subject.disablePlayableCharacter();
        REQUIRE_FALSE(sceneNode->isVisible());
    }
}
