#include <catch.hpp>
#include "leviathan.h"

TEST_CASE( "Mouse" ) {
    leviathan::input::Mouse subject;

    SECTION( "default values" ) {
        REQUIRE_FALSE( subject.isLMBDown() );
        REQUIRE_FALSE( subject.isMMBDown() );
        REQUIRE_FALSE( subject.isRMBDown() );
        REQUIRE_FALSE( subject.wasLMBDown() );
        REQUIRE_FALSE( subject.wasMMBDown() );
        REQUIRE_FALSE( subject.wasRMBDown() );
        REQUIRE( subject.getPosition() == irr::core::position2d<irr::s32>(0, 0) );
        REQUIRE( subject.getLastPosition() == irr::core::position2d<irr::s32>(0, 0) );
        REQUIRE( subject.getWheelDelta() == Approx( 0.0f ) );
    }

    SECTION( "buttons and coordinates are set asynchronous by an event receiver" ) {
        subject.setMouseButtonState( leviathan::input::Mouse::Button::LEFT, true );
        subject.setMouseCoordinateState( 10, 20 );
        subject.setMouseWheelState( 30.0f );
        REQUIRE( subject.isLMBDown() );
        REQUIRE_FALSE( subject.isMMBDown() );
        REQUIRE( subject.getPosition() == irr::core::position2d<irr::s32>(10, 20) );
        REQUIRE( subject.getWheelDelta() == Approx( 30.0f ) );
        subject.setMouseButtonState( leviathan::input::Mouse::Button::LEFT, false );
        subject.setMouseButtonState( leviathan::input::Mouse::Button::MIDDLE, true );
        subject.setMouseCoordinateState( 30, 10 );
        subject.setMouseWheelState( -2.2f );
        REQUIRE_FALSE( subject.isLMBDown() );
        REQUIRE( subject.isMMBDown() );
        REQUIRE( subject.getPosition() == irr::core::position2d<irr::s32>(30, 10) );
        REQUIRE( subject.getWheelDelta() == Approx( -2.2f ) );
    }

    SECTION( "button states and coordinates create history on update" ) {
        // subject.setKeyState( irr::KEY_KEY_Z, true, true, true );
        // REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        // REQUIRE( subject.isShiftDown() );
        // REQUIRE( subject.isCtrlDown() );
        // REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        // REQUIRE_FALSE( subject.wasShiftDown() );
        // REQUIRE_FALSE( subject.wasCtrlDown() );
        // subject.update();
        // subject.setKeyState( irr::KEY_KEY_Z, false, false, false );
        // REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        // REQUIRE_FALSE( subject.isShiftDown() );
        // REQUIRE_FALSE( subject.isCtrlDown() );
        // REQUIRE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        // REQUIRE( subject.wasShiftDown() );
        // REQUIRE( subject.wasCtrlDown() );
        //
        // SECTION( "key states are cleared without continuous input" ) {
        //     subject.update();
        //     REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.wasShiftDown() );
        //     REQUIRE_FALSE( subject.wasCtrlDown() );
        // }
    }

    SECTION( "convenience methods" ) {
        // SECTION( "key held down" ) {
        //     subject.setKeyState( irr::KEY_KEY_Z, true, false, false );
        //     subject.update();
        //     subject.setKeyState( irr::KEY_KEY_Z, true, false, false );
        //     REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        // }
        // SECTION( "key not touched" ) {
        //     subject.update();
        //     REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        // }
        // SECTION( "key just suppressed" ) {
        //     subject.setKeyState( irr::KEY_KEY_Z, true, false, false );
        //     REQUIRE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        // }
        // SECTION( "key just released" ) {
        //     subject.setKeyState( irr::KEY_KEY_Z, true, false, false );
        //     subject.update();
        //     subject.setKeyState( irr::KEY_KEY_Z, false, false, false );
        //     REQUIRE_FALSE( subject.isKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE( subject.wasKeyDown( irr::KEY_KEY_Z ) );
        //     REQUIRE_FALSE( subject.hasKeyJustBeenSuppressed( irr::KEY_KEY_Z ) );
        //     REQUIRE( subject.hasKeyJustBeenReleased( irr::KEY_KEY_Z ) );
        // }
    }
}
