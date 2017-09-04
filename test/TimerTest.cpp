#include <catch.hpp>
#include "leviathan.h"

TEST_CASE( "Timer: architecture" ) {
    leviathan::core::Timer timer( 2.0f );

    SECTION( "tick() starts chains" ) {
        timer.start();
        REQUIRE( timer.tick( 1.1f ).tick( 1.1f ).isFull() );
    }
}

TEST_CASE( "Timer: max value" ) {

    SECTION( "zero is not forbidden" ) {
        leviathan::core::Timer timer( 0.0f );
        REQUIRE( irr::core::equals( timer.getMaxValue(), 0.0f ) );
        REQUIRE( timer.isFull() );
    }

    SECTION( "negative values are not forbidden" ) {
        leviathan::core::Timer timer( -10.0f );
        REQUIRE( irr::core::equals( timer.getMaxValue(), -10.0f ) );
        REQUIRE( timer.isFull() );
    }

    SECTION( "values are exactly met" ) {
        leviathan::core::Timer timer( 1.0f );
        timer.start();
        REQUIRE( irr::core::equals( timer.getMaxValue(), 1.0f ) );
        REQUIRE_FALSE( timer.isFull() );

        timer.tick( 1.0f - irr::core::ROUNDING_ERROR_f32 );
        REQUIRE_FALSE( timer.isFull() );

        timer.tick( irr::core::ROUNDING_ERROR_f32 );
        REQUIRE( timer.isFull() );
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

    SECTION( "it can tick backwards" ) {
        timer.start();
        timer.tick( -10.0f );
        REQUIRE_FALSE( timer.isFull() );

        timer.tick( 11.9f );
        REQUIRE_FALSE( timer.isFull() );

        timer.tick( 0.2f );
        REQUIRE( timer.isFull() );

        SECTION( "but it stays full if once reached" ) {
            timer.tick( -10.0f );
            REQUIRE( timer.isFull() );
        }
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

    SECTION( "it is paused" ) {
        SECTION( "when it is paused after being started" ) {
            timer.start();
            timer.pause();
            REQUIRE( timer.isPaused() );
        }
    }

    SECTION( "it is not paused" ) {
        SECTION( "when it is newly created" ) {
            REQUIRE_FALSE( timer.isPaused() );
        }

        SECTION( "when it is started" ) {
            timer.start();
            REQUIRE_FALSE( timer.isPaused() );
        }

        SECTION( "when it is restarted" ) {
            timer.start();
            timer.restart();
            REQUIRE_FALSE( timer.isPaused() );
        }

        SECTION( "when it is resumed" ) {
            timer.start();
            timer.pause();
            timer.resume();
            REQUIRE_FALSE( timer.isPaused() );
        }

        SECTION( "when it is stopped" ) {
            timer.start();
            timer.stop();
            REQUIRE_FALSE( timer.isPaused() );
        }
    }
}
