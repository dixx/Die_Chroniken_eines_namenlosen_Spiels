#include "../../source/Leviathan/characters/Hero.h"
#include "../helpers/CatchPatches.hpp"
#include "../helpers/GraphicEngineInstance.hpp"
#include "catch.hpp"
#include "irrlicht.h"

TEST_CASE("Hero", "[integration]") {
    leviathan::characters::Hero subject("the hero", GraphicEngineInstance::get()->getSceneManager());

    SECTION("has an internal name") {
        REQUIRE(subject.getInternalName() == "the hero");
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
}
