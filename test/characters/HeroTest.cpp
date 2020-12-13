#include "../../source/Leviathan/characters/Hero.h"
#include "../helpers/CatchPatches.hpp"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "irrlicht.h"
#include <string>

TEST_CASE("Hero", "[integration]") {
    auto name = std::to_string(TestHelper::getUniqueId()).c_str();
    leviathan::characters::Hero subject(name, TestHelper::graphicEngine()->getSceneManager());
    auto sceneNode = TestHelper::graphicEngine()->getSceneManager()->getSceneNodeFromName(name);

    SECTION("has a scene node") {
        REQUIRE(sceneNode != nullptr);
    }
    SECTION("has an internal name") {
        REQUIRE(subject.getInternalName() == name);
    }
    SECTION("has 3D attributes") {
        REQUIRE(subject.getPosition() == irr::core::vector3df(0.0f, 0.0f, 0.0f));
        REQUIRE(subject.getRotation() == irr::core::vector3df(0.0f, 0.0f, 0.0f));

        SECTION("which can be changed") {
            subject.setPosition(irr::core::vector3df(1.0f, 2.0f, 3.0f));
            subject.setRotation(irr::core::vector3df(4.0f, 5.0f, 6.0f));
            REQUIRE(subject.getPosition() == irr::core::vector3df(1.0f, 2.0f, 3.0f));
            REQUIRE(subject.getRotation() == irr::core::vector3df(4.0f, 5.0f, 6.0f));
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
