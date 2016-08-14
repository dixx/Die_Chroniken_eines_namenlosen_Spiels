#include "catch.hpp"
#include "../Zufall.h"

TEST_CASE( "seeding" ) {
    Zufall& subject = Zufall::getInstance();

    SECTION( "seed evolves internally") {
        subject.start( 42 );

        REQUIRE( subject.getInt() == 1331530 );
        REQUIRE( subject.getInt() != 1331530 );
    }

    SECTION( "different seed produces different result") {
        subject.start( 43 );

        REQUIRE( subject.getInt() != 1331530 );
    }

    SECTION( "same seed produces same result every time") {
        subject.start( 42 );

        REQUIRE( subject.getInt() == 1331530 );

        SECTION( "resetting the seed with same value produces still the same result" ) {
            subject.start( 42 );

            REQUIRE( subject.getInt() == 1331530 );
        }
    }
}
