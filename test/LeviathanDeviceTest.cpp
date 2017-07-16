#include "catch.hpp"
#include "fakeit.hpp"
#include "leviathan.h"
#include "helpers/Testhelper.h"
#include "helpers/TesthelperLeviathanDevice.h"

using namespace fakeit;

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
        Mock<leviathan::core::GameState> gameStateDouble;
        Fake( Method( gameStateDouble, update ), Method( gameStateDouble, draw ) );
        leviathan::core::GameState &gameState = gameStateDouble.get();
        subject.GameStateManager().add( gameState, 1234 );
        subject.GameStateManager().transitTo( 1234 );
        subject.GameStateManager().update( 12.34f );
        Verify( Method( gameStateDouble, draw ) ).Exactly( 0 );
        Verify( Method( gameStateDouble, update ).Using( 12.34f ) ).Once();
        subject.GameStateManager().draw();
        Verify( Method( gameStateDouble, draw ) ).Once();
        VerifyNoOtherInvocations( Method( gameStateDouble, update ) );
    }
}

TEST_CASE( "LeviathanDevice main loop" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\nmax_fps=100\nscreen_x=5\nscreen_y=5\n" );
    TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock subject;
    subject.init( configFileName );
    subject.enableMock(); // TODO inject mock?
    IrrlichtDeviceMock& graphicEngineMock = subject.mockedGraphicEngine; // TODO repace with mock

    Mock<leviathan::core::GameState> gameStateDouble;
    Fake( Method( gameStateDouble, update ), Method( gameStateDouble, draw ) );
    leviathan::core::GameState &gameState = gameStateDouble.get();
    subject.GameStateManager().add( gameState, 42 );
    subject.GameStateManager().transitTo( 42 );

    SECTION( "it should be fair to other apps if inactive" ) {
        graphicEngineMock.letRunReturnByDefault( false );
        graphicEngineMock.letRunReturn( true );
        graphicEngineMock.letRunReturn( true );
        graphicEngineMock.letRunReturn( true );
        graphicEngineMock.letRunReturn( true );
        graphicEngineMock.letRunReturn( true );
        graphicEngineMock.letIsWindowActiveReturnByDefault( true );
        graphicEngineMock.letIsWindowActiveReturn( true );
        graphicEngineMock.letIsWindowActiveReturn( true );
        graphicEngineMock.letIsWindowActiveReturn( false );
        graphicEngineMock.letIsWindowActiveReturn( false );
        graphicEngineMock.letIsWindowActiveReturn( true );
        subject.run();
        REQUIRE( graphicEngineMock.timesYieldWasCalled() == 2 );
    }

    SECTION( "it should not draw if engine is shut down directly after game state update" ) {
    }

    SECTION( "without calculation stress" ) {
        SECTION( "it should draw with a fixed maximum frame rate" ) {
            SECTION( "and it should update every cycle" ) {
            }
        }
    }
    SECTION( "with sometimes zero elapsed time" ) {
        SECTION( "it should draw with a fixed maximum frame rate" ) {
            SECTION( "and it should update every cycle" ) {
            }
        }
    }
    SECTION( "with moderate calculation stress" ) {
        SECTION( "it should begin to skip frames" ) {
            SECTION( "but it should update every cycle" ) {
            }
        }
    }
    SECTION( "with much calculation stress" ) {
        SECTION( "it should draw with a fixed minimum frame rate" ) {
            SECTION( "but it should update every cycle" ) {
            }
        }
    }
    SECTION( "with peak load" ) {
        SECTION( "it should draw with a fixed minimum frame rate" ) {
            SECTION( "but it should update every cycle" ) {
            }
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
