#include "catch.hpp"
#include "leviathan.h"
#include "Testhelper.h"
#include "TesthelperLeviathan.h"

TEST_CASE( "LeviathanDevice supporter" ) {
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
        SECTION( "it can write a config file" ) {}
    }
    SECTION( "it provides a ready-to-use GameStateManager" ) {
        TesthelperLeviathan::GameStateSub gameState;
        subject.GameStateManager().add( gameState, 1 );
        subject.GameStateManager().transitTo( 1 );
        subject.GameStateManager().update( 12.34f );
        REQUIRE_FALSE( gameState.isDrawn );
        REQUIRE( gameState.isUpdated );
        REQUIRE( gameState.delta == Approx( 12.34f ) );
        subject.GameStateManager().draw();
        REQUIRE( gameState.isDrawn );
        REQUIRE( gameState.isUpdated );
        REQUIRE( gameState.delta == Approx( 12.34f ) );
    }
}
