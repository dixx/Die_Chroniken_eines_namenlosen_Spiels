#include "catch.hpp"
#include "leviathan.h"

TEST_CASE( "TimeControl: ticking" ) {
    leviathan::core::TimeControl subject;
    leviathan::core::Timer timer( 2.0f );
    timer.start();
    subject.add( timer );

    SECTION( "it forwards the value to the timers" ) {
        subject.tick( -10.0f );
        REQUIRE_FALSE( timer.isFull() );

        subject.tick( 11.9f );
        REQUIRE_FALSE( timer.isFull() );

        subject.tick( 0.2f );
        REQUIRE( timer.isFull() );
    }
}

TEST_CASE( "TimeControl: functionality" ) {
    leviathan::core::TimeControl subject;
    leviathan::core::Timer timer1( 1.0f );
    leviathan::core::Timer timer2( 2.0f );
    timer1.start();
    timer2.start();

    SECTION( "Timers added to TimeControl" ) {
        subject.add( timer1 );
        subject.add( timer2 );

        SECTION( "can be incremented" ) {
            subject.tick( 1.0f );
            REQUIRE( timer1.isFull() );
            REQUIRE_FALSE( timer2.isFull() );
            subject.tick( 4.0f );
            REQUIRE( timer1.isFull() );
            REQUIRE( timer2.isFull() );
        }

        SECTION( "can be paused" ) {
            subject.pause();
            REQUIRE( timer1.isPaused() );
            REQUIRE( timer2.isPaused() );

            SECTION( "and resumed" ) {
                subject.resume();
                REQUIRE_FALSE( timer1.isPaused() );
                REQUIRE_FALSE( timer2.isPaused() );
            }
        }

        SECTION( "can be removed" ) {
            subject.remove( timer2 );
            subject.tick( 4.0f );
            REQUIRE( timer1.isFull() );
            REQUIRE_FALSE( timer2.isFull() );
        }
    }

    SECTION( "Timers not added to TimeControl" ) {
        SECTION( "cannot be incremented" ) {
            subject.tick( 4.0f );
            REQUIRE_FALSE( timer1.isFull() );
        }

        SECTION( "cannot be paused" ) {
            subject.pause();
            REQUIRE_FALSE( timer1.isPaused() );

            SECTION( "nor resumed" ) {
                timer1.pause();
                subject.resume();
                REQUIRE( timer1.isPaused() );
            }
        }
    }
}
