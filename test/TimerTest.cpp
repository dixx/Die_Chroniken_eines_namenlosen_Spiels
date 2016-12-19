#include "catch.hpp"
#include "../source/Leviathan/leviathan.h"
#include <time.h>

TEST_CASE( "Timer: architecture" ) {
    SECTION( "it is not a static instance" ) {
        leviathan::core::Timer timer1( 1.0f );
        leviathan::core::Timer timer2( 1.0f );

        REQUIRE( &timer1 != &timer2 );
    }
}

TEST_CASE( "Timer: ticking" ) {
    leviathan::core::Timer timer( 2.0f );

    SECTION( "it does not tick" ) {

        SECTION( "when it is not started" ) {
            timer.tick( 2.2f );

            REQUIRE_FALSE( timer.isFull() );
        }

        SECTION( "when it is paused" ) {
            timer.start();
            timer.pause();
            timer.tick( 2.2f );

            REQUIRE_FALSE( timer.isFull() );
        }
    }

    SECTION( "it does tick" ) {

        SECTION( "when it is started" ) {
            timer.start();
            timer.tick( 2.2f );

            REQUIRE( timer.isFull() );
        }

        SECTION( "when it is resumed" ) {
            timer.start();
            timer.pause();
            timer.resume();
            timer.tick( 2.2f );

            REQUIRE( timer.isFull() );
        }
    }
}
