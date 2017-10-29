#include <catch.hpp>
#include "leviathan.h"

TEST_CASE( "Keyboard" ) {
    leviathan::input::Keyboard subject;

    SECTION( "default values" ) {
        REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
        REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        REQUIRE_FALSE( subject.isShiftDown() );
        REQUIRE_FALSE( subject.wasShiftDown() );
        REQUIRE_FALSE( subject.isCtrlDown() );
        REQUIRE_FALSE( subject.wasCtrlDown() );
    }

    SECTION( "keys are set asynchronous by an event receiver" ) {
        subject.setKeyState( irr::KEY_KEY_Z, true );
        REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        subject.setKeyState( irr::KEY_KEY_Z, false );
        REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
    }

    SECTION( "key states create history on update" ) {
        subject.setKeyState( irr::KEY_KEY_Z, true );
        REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        subject.update();
        subject.setKeyState( irr::KEY_KEY_Z, false );
        REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        REQUIRE( subject.wasKeyDown( irr::KEY_KEY_Z ) );

        SECTION( "key states are cleared without continuous input" ) {
            subject.update();
            REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        }
    }

    SECTION( "key state convenience methods" ) {
        SECTION( "key held down" ) {
            subject.setKeyState( irr::KEY_KEY_Z, true );
            subject.update();
            subject.setKeyState( irr::KEY_KEY_Z, true );
            REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        }
        SECTION( "key not touched" ) {
            subject.update();
            REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        }
        SECTION( "key just suppressed" ) {
            subject.setKeyState( irr::KEY_KEY_Z, true );
            REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        }
        SECTION( "key just released" ) {
            subject.setKeyState( irr::KEY_KEY_Z, true );
            subject.update();
            subject.setKeyState( irr::KEY_KEY_Z, false );
            REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
            REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
            REQUIRE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        }
    }
}
