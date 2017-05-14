#include "catch.hpp"
#include "leviathan.h"

class GameStateSub final: public leviathan::core::GameState
{
public:
    bool isDrawn, isUpdated;
    irr::f32 delta;

    GameStateSub() : isDrawn(false), isUpdated(false), delta(0.0f) {};

    void draw() final
    {
        isDrawn = true;
    }

    void update( const irr::f32 frameDeltaTime ) final
    {
        isUpdated = true;
        delta = frameDeltaTime;
    }
}; // TODO try to remove this duplicate!

TEST_CASE( "GameStateManager: add game states" ) {
    leviathan::core::GameStateManager subject;
    GameStateSub start, play, stop;
    subject.add( start, 1 );
    subject.add( play, 2 );
    REQUIRE( subject.getGameStateCount() == 2 );

    SECTION( "indexes are just numbers" ) {
        subject.add( stop, 17 );
        REQUIRE( subject.getGameStateCount() == 3 );
    }

    SECTION( "indexes are unique, states are not, and the manager is not whiny about it" ) {
        subject.add( start, 1 );
        REQUIRE( subject.getGameStateCount() == 2 );
        subject.add( start, 4 );
        REQUIRE( subject.getGameStateCount() == 3 );
        subject.add( play, 1 );
        REQUIRE( subject.getGameStateCount() == 3 );
    }
}

TEST_CASE( "GameStateManager: transit between game states" ) {
    leviathan::core::GameStateManager subject;

    SECTION( "transit to state that is not on the stack" ) {
        // state is pushed onto the stack
        // state is made active
        REQUIRE( true );
    }
    SECTION( "transit to state that is on top of stack" ) {
        // nothing changes
        REQUIRE( true );
    }
    SECTION( "transit to state that is second place of stack" ) {
        // top state is popped from the stack
        // state is made active
        REQUIRE( true );
    }
    SECTION( "transit to state that is further down the stack" ) {
        // nothing changes
        REQUIRE( true );
    }
}
