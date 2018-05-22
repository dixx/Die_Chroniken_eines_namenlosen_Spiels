#include <catch.hpp>
#include "leviathan.h"

TEST_CASE( "Actions" ) {
    leviathan::input::Actions subject;

    SECTION( "single action mapping" ) {
        SECTION( "has attributes" ) {
            // has name, primary, secondary, ...
        }
        SECTION( "can handle different input types" ) {}
    }

    SECTION( "reads action map from game state" ) {
        SECTION( "provides action for each defined input mapping" ) {}
    }

    SECTION( "reads action map from user profile" ) {}

    SECTION( "error handling" ) {}
}
