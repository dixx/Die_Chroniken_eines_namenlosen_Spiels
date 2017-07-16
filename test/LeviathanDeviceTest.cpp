#include "catch.hpp"
#include "leviathan.h"
#include "Testhelper.h"
#include "TesthelperGameState.h"
#include "TesthelperLeviathanDevice.h"

TEST_CASE( "LeviathanDevice supporter" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\ncolor_depth=42\nscreen_x=32\nscreen_y=20\n" );
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
        TesthelperGameState::GameStateSub gameState;
        subject.GameStateManager().add( gameState, 1234 );
        subject.GameStateManager().transitTo( 1234 );
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

TEST_CASE( "LeviathanDevice main loop" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\nmax_fps=42\nscreen_x=5\nscreen_y=5\n" );
    TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock subject;
    subject.init( configFileName );

    SECTION( "it should be fair to other apps if inactive" ) {
        subject.enableMock();
        subject.mockedGraphicEngine.letRunReturnByDefault( false );
        subject.mockedGraphicEngine.letRunReturn( true );
        subject.mockedGraphicEngine.letRunReturn( true );
        subject.mockedGraphicEngine.letRunReturn( true );
        subject.mockedGraphicEngine.letRunReturn( true );
        subject.mockedGraphicEngine.letRunReturn( true );
        subject.mockedGraphicEngine.letIsWindowActiveReturnByDefault( true );
        subject.mockedGraphicEngine.letIsWindowActiveReturn( true );
        subject.mockedGraphicEngine.letIsWindowActiveReturn( true );
        subject.mockedGraphicEngine.letIsWindowActiveReturn( false );
        subject.mockedGraphicEngine.letIsWindowActiveReturn( false );
        subject.mockedGraphicEngine.letIsWindowActiveReturn( true );
        subject.run();
        REQUIRE( subject.mockedGraphicEngine.timesYieldWasCalled() == 2 );
    }

    SECTION( "it should not draw if engine is shut down directly after game state update" ) {
    }

    SECTION( "without calculation stress" ) {
        SECTION( "it should draw with a fixed maximum frame rate" ) {
        }
        SECTION( "it should update every tick" ) {
        }
    }
    SECTION( "with zero elapsed time" ) {
        SECTION( "it should draw with a fixed maximum frame rate" ) {
        }
        SECTION( "it should update every tick" ) {
        }
    }
    SECTION( "with moderate calculation stress" ) {
        SECTION( "it should begin to skip frames" ) {
        }
        SECTION( "it should update every tick" ) {
        }
    }
    SECTION( "with much calculation stress" ) {
        SECTION( "it should draw with a fixed minimum frame rate" ) {
        }
        SECTION( "it should update every tick" ) {
        }
    }
    SECTION( "with peak load" ) {
        SECTION( "it should draw with a fixed minimum frame rate" ) {
        }
        SECTION( "it should update every tick" ) {
        }
    }
}

TEST_CASE( "LeviathanDevice exit status" ) {
    leviathan::LeviathanDevice subject;
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\nscreen_x=32\nscreen_y=20\n" );

    SECTION( "it is 0 if everything ran well" ) {
        REQUIRE( 0 == subject.exitStatus() );
        subject.init( configFileName );
        REQUIRE( 0 == subject.exitStatus() );
    }
}
