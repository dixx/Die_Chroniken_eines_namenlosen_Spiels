#include "catch.hpp"
#include "leviathan.h"

TEST_CASE( "TimeControl: architecture" ) {
    leviathan::core::TimeControl subject;

    SECTION( "it is not a static instance" ) {
        leviathan::core::TimeControl sample;
        REQUIRE( &subject != &sample );
    }
}
