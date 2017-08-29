#include "catch.hpp"
#include "leviathan.h"

class GameStateSub final: public leviathan::core::GameState
{
public:
    bool isDrawn, isUpdated;
    float delta;

    GameStateSub() : isDrawn(false), isUpdated(false), delta(0.0f) {};

    void draw() final
    {
        isDrawn = true;
    }

    void update( const float frameDeltaTime ) final
    {
        isUpdated = true;
        delta = frameDeltaTime;
    }
};

TEST_CASE( "GameState: interface methods" ) {
    GameStateSub sample;
    leviathan::core::GameState* subject = &sample;
    subject->draw();
    REQUIRE( sample.isDrawn );
    REQUIRE_FALSE( sample.isUpdated );
    subject->update( 42.21f );
    REQUIRE( sample.isDrawn );
    REQUIRE( sample.isUpdated );
    REQUIRE( sample.delta == Approx( 42.21f ) );
}
