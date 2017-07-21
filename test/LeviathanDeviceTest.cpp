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
        subject.GameStateManager().add( gameStateDouble.get(), 1234 );
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
    Mock<irr::ITimer> timerDouble;
    static irr::u32 timeDelta = 0;
    When( Method( timerDouble, getTime ) ).AlwaysReturn( 0 );
    Mock<irr::IrrlichtDevice> graphicEngineDouble;
    Fake( Method( graphicEngineDouble, yield ) );
    When( Method( graphicEngineDouble, getTimer ) ).AlwaysReturn( &(timerDouble.get()) );
    When( Method( graphicEngineDouble, isWindowActive ) ).AlwaysReturn( true );
    subject.injectMockedGraphicEngine( graphicEngineDouble.get() );
    Mock<leviathan::core::GameState> gameStateDouble;
    Fake( Method( gameStateDouble, update ), Method( gameStateDouble, draw ) );
    subject.GameStateManager().add( gameStateDouble.get(), 42 );
    subject.GameStateManager().transitTo( 42 );

    SECTION( "it should be fair to other apps if inactive" ) {
        When( Method( graphicEngineDouble, run ) ).Return( 5_Times( true ), false );
        When( Method( graphicEngineDouble, isWindowActive ) ).Return( true, true, false, false, true );
        subject.run();
        Verify( Method( graphicEngineDouble, yield ) ).Exactly( 2_Times );
    }

    SECTION( "it should not draw if engine is shut down directly after game state update" ) {
        When( Method( graphicEngineDouble, run ) ).Return( true, false );
        subject.run();
        Verify( Method( gameStateDouble, draw ) ).Exactly( 0_Times );
    }

    SECTION( "without calculation stress" ) {
        When( Method( graphicEngineDouble, run ) ).Return( 1000_Times( true ), false );
        When( Method( timerDouble, getTime ) ).AlwaysDo( []{ return timeDelta++; } );
        subject.run();
        SECTION( "it should draw with a fixed maximum frame rate" ) {
            Verify( Method( gameStateDouble, draw ) ).Exactly( 100_Times );
            SECTION( "and it should update every cycle" ) {
                Verify( Method( gameStateDouble, update ) ).Exactly( 100_Times );
            }
        }
    }

    SECTION( "with sometimes zero elapsed time" ) {
        When( Method( graphicEngineDouble, run ) ).Return( 2000_Times( true ), false );
        When( Method( timerDouble, getTime ) ).AlwaysDo( []{ return timeDelta&1 ? timeDelta++ : timeDelta; } );
        subject.run();
        SECTION( "it should draw with a fixed maximum frame rate" ) {
            Verify( Method( gameStateDouble, draw ) ).Exactly( 100_Times );
            SECTION( "and it should update every cycle" ) {
                Verify( Method( gameStateDouble, update ) ).Exactly( 100_Times );
            }
        }
    }

    SECTION( "with moderate calculation stress" ) {
        // this needs a better approach. The assumption is that draw() needs much more time than update().
        SECTION( "it should begin to skip frames" ) {
            SECTION( "but it should update every cycle" ) {
            }
        }
    }

    SECTION( "with much calculation stress" ) {
        // this needs a better approach. The assumption is that draw() needs much more time than update().
        SECTION( "it should draw with a fixed minimum frame rate" ) {
            SECTION( "but it should update every cycle" ) {
            }
        }
    }

    SECTION( "with peak load" ) {
        // this needs a better approach. The assumption is that draw() needs much more time than update().
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
