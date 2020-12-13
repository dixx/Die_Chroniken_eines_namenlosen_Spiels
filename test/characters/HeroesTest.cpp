#include "../../source/Leviathan/characters/Heroes.h"
#include "../helpers/OverloadedOperators.hpp"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "irrlicht.h"

TEST_CASE("Heroes", "[integration]") {
    leviathan::characters::Heroes subject(TestHelper::graphicEngine()->getSceneManager());

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
