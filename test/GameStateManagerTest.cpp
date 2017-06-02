#include "catch.hpp"
#include "leviathan.h"
#include "helpers/TesthelperGameState.h"

TEST_CASE( "GameStateManager: add game states" ) {
    leviathan::core::GameStateManager subject;
    TesthelperGameState::GameStateSub start, play, stop;
    enum { STATE_START = 1, STATE_PLAY, STATE_STOP };
    subject.add( start, STATE_START );
    subject.add( play, STATE_PLAY );
    REQUIRE( subject.getGameStateCount() == 2 );

    SECTION( "indexes are just numbers" ) {
        subject.add( stop, 17 );
        REQUIRE( subject.getGameStateCount() == 3 );
    }

    SECTION( "indexes are unique, states are not, and the manager is not whiny about it" ) {
        subject.add( start, STATE_START );
        REQUIRE( subject.getGameStateCount() == 2 );
        subject.add( start, 4 );
        REQUIRE( subject.getGameStateCount() == 3 );
        subject.add( play, STATE_START );
        REQUIRE( subject.getGameStateCount() == 3 );
    }
}

TEST_CASE( "GameStateManager: transit between game states" ) {
    leviathan::core::GameStateManager subject;
    TesthelperGameState::GameStateSub start, play, pause, options;
    enum { STATE_START = 1, STATE_PLAY, STATE_PAUSE, STATE_OPTIONS };
    subject.add( start, STATE_START );
    subject.add( options, STATE_OPTIONS );
    subject.add( pause, STATE_PAUSE );
    subject.add( play, STATE_PLAY );

    SECTION( "it activates the requested state if transit to state that is not on the stack" ) {
        subject.transitTo( STATE_START );
        REQUIRE( subject.getActiveStateID() == STATE_START );
        subject.transitTo( STATE_PLAY );
        REQUIRE( subject.getActiveStateID() == STATE_PLAY );
    }
    SECTION( "it activates the requested state if transit to state that is second place of stack" ) {
        subject.transitTo( STATE_START );
        subject.transitTo( STATE_OPTIONS );
        subject.transitTo( STATE_PLAY );
        subject.transitTo( STATE_PAUSE );
        subject.transitTo( STATE_PLAY );
        REQUIRE( subject.getActiveStateID() == STATE_PLAY );
    }
    SECTION( "it changes nothing if transit to state that is on top of stack" ) {
        subject.transitTo( STATE_START );
        subject.transitTo( STATE_START );
        REQUIRE( subject.getActiveStateID() == STATE_START );
        subject.transitTo( STATE_PLAY );
        subject.transitTo( STATE_PLAY );
        REQUIRE( subject.getActiveStateID() == STATE_PLAY );
    }
    SECTION( "it changes nothing if transit to state that is further down the stack" ) {
        subject.transitTo( STATE_START );
        subject.transitTo( STATE_PLAY );
        subject.transitTo( STATE_PAUSE );
        subject.transitTo( STATE_START );
        REQUIRE( subject.getActiveStateID() == STATE_PAUSE );
    }
}

TEST_CASE( "GameStateManager: update and draw active game states" ) {
    leviathan::core::GameStateManager subject;
    TesthelperGameState::GameStateSub start, play, pause;
    enum { STATE_START = 1, STATE_PLAY, STATE_PAUSE };
    subject.add( start, STATE_START );
    subject.add( play, STATE_PLAY );
    subject.add( pause, STATE_PAUSE );

    SECTION( "it updates and draws the active state") {
        subject.transitTo( STATE_START );
        subject.draw();
        subject.update( 1.1f );
        REQUIRE( start.isDrawn );
        REQUIRE( start.isUpdated );
        REQUIRE( start.delta == Approx( 1.1f ) );

        SECTION( "and only the active state is drawn and updated" ) {
            subject.transitTo( STATE_PLAY );
            subject.transitTo( STATE_PAUSE );
            subject.draw();
            subject.update( 23.456f );
            REQUIRE( start.delta == Approx( 1.1f ) );
            REQUIRE_FALSE( play.isDrawn );
            REQUIRE_FALSE( play.isUpdated );
            REQUIRE( pause.isDrawn );
            REQUIRE( pause.isUpdated );
            REQUIRE( pause.delta == Approx( 23.456f ) );
        }
    }
}
