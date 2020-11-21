#include "../../source/Leviathan/characters/Heroes.h"
#include "../helpers/GraphicEngineInstance.hpp"
#include "../helpers/OverloadedOperators.hpp"
#include "catch.hpp"
#include "irrlicht.h"

TEST_CASE("Heroes", "[unit]") {
    leviathan::characters::Heroes subject(GraphicEngineInstance::get()->getSceneManager());

    SECTION("can create default heroes") {
        REQUIRE(subject.create().getInternalName() == "");
    }

    SECTION("can activate one hero") {
        auto someHero = subject.create("John Doe");
        auto anotherHero = subject.create("Jane Doe");

        subject.activate("John Doe");
        REQUIRE(subject.getActiveHero() == someHero);
        subject.activate("Jane Doe");
        REQUIRE(subject.getActiveHero() == anotherHero);
        subject.activate("Jean Doe");
        REQUIRE(subject.getActiveHero() == anotherHero);
    }
}
