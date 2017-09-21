#include <catch.hpp>
#include "leviathan.h"

TEST_CASE( "Keyboard" ) {
    leviathan::input::Keyboard subject;

    SECTION( "default values" ) {
        REQUIRE_FALSE( subject.isKeyDown( 42 ) );
        REQUIRE_FALSE( subject.wasKeyDown( 42 ) );
        REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( 42 ) );
        REQUIRE_FALSE( subject.hasKeyJustBeenReleased( 42 ) );
        // REQUIRE_FALSE( subject.isShiftDown() );
        // REQUIRE_FALSE( subject.wasShiftDown() );
        // REQUIRE_FALSE( subject.isCtrlDown() );
        // REQUIRE_FALSE( subject.wasCtrlDown() );
    }

    SECTION( "keys are set asynchronous by an event receiver" ) {
        REQUIRE_FALSE( subject.isKeyDown( 42 ) );
        subject.setKeyState( 42, true );
        REQUIRE( subject.isKeyDown( 42 ) );
        subject.setKeyState( 42, false );
        REQUIRE_FALSE( subject.isKeyDown( 42 ) );
    }

    SECTION( "key states create history at update" ) {
        subject.setKeyState( 42, true );
        REQUIRE( subject.isKeyDown( 42 ) );
        REQUIRE_FALSE( subject.wasKeyDown( 42 ) );
        subject.update();
        subject.setKeyState( 42, false );
        REQUIRE_FALSE( subject.isKeyDown( 42 ) );
        REQUIRE( subject.wasKeyDown( 42 ) );

        SECTION( "key states are cleared without continuous input" ) {
            subject.update();
            REQUIRE_FALSE( subject.wasKeyDown( 42 ) );
        }
    }

    SECTION( "key state convenience methods" ) {
        SECTION( "key held down" ) {
            subject.setKeyState( 42, true );
            subject.update();
            subject.setKeyState( 42, true );
            REQUIRE( subject.isKeyDown( 42 ) );
            REQUIRE( subject.wasKeyDown( 42 ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( 42 ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenReleased( 42 ) );
        }
        SECTION( "key not touched" ) {
            subject.update();
            REQUIRE_FALSE( subject.isKeyDown( 42 ) );
            REQUIRE_FALSE( subject.wasKeyDown( 42 ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( 42 ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenReleased( 42 ) );
        }
        SECTION( "key just suppressed" ) {
            subject.setKeyState( 42, true );
            REQUIRE( subject.isKeyDown( 42 ) );
            REQUIRE_FALSE( subject.wasKeyDown( 42 ) );
            REQUIRE( subject.hasKeyJustBeenSuppressed( 42 ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenReleased( 42 ) );
        }
        SECTION( "key just released" ) {
            subject.setKeyState( 42, true );
            subject.update();
            subject.setKeyState( 42, false );
            REQUIRE_FALSE( subject.isKeyDown( 42 ) );
            REQUIRE( subject.wasKeyDown( 42 ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( 42 ) );
            REQUIRE( subject.hasKeyJustBeenReleased( 42 ) );
        }
    }
}
