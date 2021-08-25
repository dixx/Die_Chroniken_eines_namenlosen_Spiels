#include "../../src/Leviathan/characters/Heroes.h"
#include "../../src/Leviathan/world/NodeManager.h"
#include "../helpers/OverloadedOperators.hpp"
#include "../helpers/TestHelper.h"
#include "ISceneManager.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include <characters/CharacterConfiguration.h>
#include <characters/IHero.h>

TEST_CASE("Heroes", "[integration]") {
    leviathan::world::NodeManager nodeManager(TestHelper::graphicEngine()->getSceneManager());
    leviathan::characters::Heroes subject(nodeManager);
    TestHelper::graphicEngine()->getSceneManager()->addSphereMesh(
        "path/to/meshFile");  // add a test mesh to avoid getting a nullptr
    irr::core::dimension2du size(1, 1);
    TestHelper::graphicEngine()->getVideoDriver()->addTexture(
        size, "path/to/textureFile");  // add a test texture to avoid getting a nullptr
    leviathan::characters::CharacterConfiguration heroConfig(
        {"", "", {"path/to/meshFile", "path/to/textureFile", {}, {}, {}, {}}});

    SECTION("can create default heroes") {
        REQUIRE(subject.create(heroConfig).getInternalName() == "");
    }

    SECTION("can activate one hero") {
        heroConfig.internalName = "John Doe";
        leviathan::characters::IHero& someHero = subject.create(heroConfig);
        heroConfig.internalName = "Jane Doe";
        leviathan::characters::IHero& anotherHero = subject.create(heroConfig);

        subject.activate("John Doe");
        REQUIRE(subject.getActiveHero() == someHero);
        subject.activate("Jane Doe");
        REQUIRE(subject.getActiveHero() == anotherHero);
        subject.activate("Jean Doe");
        REQUIRE(subject.getActiveHero() == anotherHero);
    }
}
