#include "catch.hpp"
#include "leviathan.h"
#include "Testhelper.h"

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

TEST_CASE( "LeviathanDevice" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\ncolor_depth=42\nscreen_x=320\nscreen_y=200\n" );
    leviathan::LeviathanDevice subject;

    SECTION( "it provides a ready-to-use Logger" ) {
        subject.Logger().text = L"it works!";
        REQUIRE( subject.Logger().text == L"it works!" );
        subject.init( configFileName );
        subject.Logger().text = L"it still works!";
        REQUIRE( subject.Logger().text == L"it still works!" );
    }
    SECTION( "it provides a ready-to-use TimeControl" ) {
        leviathan::core::Timer timer( 123 );
        subject.TimeControl().add( timer );
        timer.start();
        subject.TimeControl().pause();
        REQUIRE( timer.isPaused() );
    }
    SECTION( "it provides a ready-to-use Configuration" ) {
        REQUIRE( subject.Configuration().getGraphicEngineParams().Bits == 16 );
        subject.init( configFileName );
        REQUIRE( subject.Configuration().getGraphicEngineParams().Bits == 42 );
    }
    SECTION( "it provides a ready-to-use GameStateManager" ) {
        GameStateSub gameState;
        subject.GameStateManager().add( gameState, 1 );
        subject.GameStateManager().update( 12.34f );
        REQUIRE_FALSE( gameState.isDrawn );
        REQUIRE( gameState.isUpdated );
        REQUIRE( gameState.delta == Approx( 12.34f ) );
        subject.GameStateManager().draw();
        REQUIRE( gameState.isDrawn );
        REQUIRE( gameState.isUpdated );
        REQUIRE( gameState.delta == Approx( 12.34f ) );
    }
    SECTION( "it can write a config file" ) {}
}
