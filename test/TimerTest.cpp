#include "catch.hpp"
#include "../source/Leviathan/leviathan.h"

TEST_CASE( "Timer: architecture" ) {
    leviathan::core::Timer timer( 2.0f );

    SECTION( "it is not a static instance" ) {
        leviathan::core::Timer timer2( 2.0f );

        REQUIRE( &timer != &timer2 );
    }

    SECTION( "tick() starts chains" ) {
        timer.start();

        REQUIRE( timer.tick( 1.1f ).tick( 1.1f ).isFull() );
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

        SECTION( "when it is stopped" ) {
            timer.start();
            timer.stop();
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

        SECTION( "when it is restarted" ) {
            timer.start();
            timer.restart();
            timer.tick( 2.2f );

            REQUIRE( timer.isFull() );
        }
    }

    SECTION( "it can tick more than once" ) {
        timer.start();

        timer.tick( 0.6f );
        timer.tick( 0.6f );
        REQUIRE_FALSE( timer.isFull() );

        timer.tick( 0.6f );
        timer.tick( 0.6f );
        REQUIRE( timer.isFull() );
    }
}

TEST_CASE( "Timer: states" ) {
    leviathan::core::Timer timer( 2.0f );

    SECTION( "it is not running" ) {
        SECTION( "when it is newly created" ) {
            REQUIRE_FALSE( timer.isRunning() );
        }

        SECTION( "when it is stopped" ) {
            timer.start();
            timer.stop();

            REQUIRE_FALSE( timer.isRunning() );
        }
    }


    SECTION( "it is running" ) {
        SECTION( "when it is started" ) {
            timer.start();

            REQUIRE( timer.isRunning() );

            SECTION( "and when it is paused" ) {
                timer.pause();

                REQUIRE( timer.isRunning() );

                SECTION( "and when it is resumed" ) {
                    timer.resume();

                    REQUIRE( timer.isRunning() );
                }
            }

            SECTION( "and when it is restarted" ) {
                timer.restart();

                REQUIRE( timer.isRunning() );
            }
        }
    }
}
