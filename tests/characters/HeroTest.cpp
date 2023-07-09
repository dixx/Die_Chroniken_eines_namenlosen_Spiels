#include "../../src/Leviathan/characters/Hero.h"
#include "../../src/Leviathan/video/Textures.h"
#include "../../src/Leviathan/world/NodeManager.h"
#include "../helpers/CatchPatches.hpp"
#include "../helpers/OverloadedOperators.hpp"
#include "../helpers/TestHelper.h"
#include "ISceneManager.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <characters/CharacterConfiguration.h>
#include <string>
#include <video/Vector3D.h>

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)
#define MAX_ROUNDING_ERROR 0.000001

TEST_CASE("Hero", "[integration]") {
    auto name = std::to_string(TestHelper::getUniqueId()).c_str();
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile");  // add a test mesh to avoid getting a nullptr
    irr::core::dimension2du size(1, 1);
    TestHelper::graphicEngine()->getVideoDriver()->addTexture(
        size, "path/to/textureFile");  // add a test texture to avoid getting a nullptr
    leviathan::characters::CharacterConfiguration heroConfig(
        {"name", name, {"path/to/meshFile", "path/to/textureFile", {}, {}, {}, {}}});
    Mock<irr::video::ITexture> textureMock;
    Mock<irr::video::IVideoDriver> videoDriverMock;
    When(OverloadedMethod(videoDriverMock, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
    Fake(Method(videoDriverMock, setTextureCreationFlag));
    leviathan::video::Textures textures(&videoDriverMock.get(), TestHelper::Logger());

    leviathan::world::NodeManager nodeManager(TestHelper::graphicEngine()->getSceneManager(), textures);
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
    SECTION("can move towards a set position") {
        subject.setPosition({0.0f, 0.0f, 0.0f});
        subject.setRotation({0.0f, 0.0f, 0.0f});
        subject.moveTo({1.0f, 0.0f, 1.0f});

        REQUIRE(subject.getPosition() == leviathan::video::Position3D({0.0f, 0.0f, 0.0f}));
        REQUIRE_THAT(subject.getRotation().x, Catch::Matchers::WithinAbs(0.0, MAX_ROUNDING_ERROR));
        REQUIRE_THAT(subject.getRotation().y, Catch::Matchers::WithinAbs(45.0, MAX_ROUNDING_ERROR));
        REQUIRE_THAT(subject.getRotation().z, Catch::Matchers::WithinAbs(0.0, MAX_ROUNDING_ERROR));

        SECTION("when updated") {
            subject.update(1.0f);
            REQUIRE_THAT(subject.getPosition().x, Catch::Matchers::WithinAbs(2.2627416, MAX_ROUNDING_ERROR));
            REQUIRE_THAT(subject.getPosition().y, Catch::Matchers::WithinAbs(0.0, MAX_ROUNDING_ERROR));
            REQUIRE_THAT(subject.getPosition().z, Catch::Matchers::WithinAbs(2.2627416, MAX_ROUNDING_ERROR));
        }
    }
}
