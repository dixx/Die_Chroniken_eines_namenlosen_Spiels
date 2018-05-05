#include <catch.hpp>
#include <fakeit.hpp>
#include <irrlicht.h>
#include <cstdint>
#include <cstdlib>
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
        Verify( Method( gameStateDouble, draw ) ).Exactly( 0_Times );
        Verify( Method( gameStateDouble, update ).Using( 12.34f ) ).Once();
        subject.GameStateManager().draw();
        Verify( Method( gameStateDouble, draw ) ).Once();
        VerifyNoOtherInvocations( Method( gameStateDouble, update ) );
    }
    SECTION( "it provides keyboard access" ) {
        REQUIRE_FALSE( subject.Keyboard().isKeyDown( irr::KEY_KEY_Z ) );
    }
    SECTION( "it provides mouse access" ) {
        REQUIRE_FALSE( subject.Mouse().isRMBDown() );
    }
}

TEST_CASE( "LeviathanDevice main loop" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\nmax_fps=100\nscreen_x=5\nscreen_y=5\n" );
    TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock subject;
    subject.init( configFileName );
    Mock<irr::ITimer> timerDouble;
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

    SECTION( "performance tests" ) {
        uint32_t virtualTime = 0;
        When( Method( timerDouble, getTime ) ).AlwaysDo( [&virtualTime]{ return virtualTime++; } );
        When( Method( graphicEngineDouble, run ) ).AlwaysDo( [&virtualTime]{ return virtualTime < 1000; } );

        SECTION( "without calculation stress" ) {
            subject.run();
            SECTION( "it should draw with a fixed maximum frame rate" ) {
                Verify( Method( gameStateDouble, draw ) ).Exactly( 100_Times );
                SECTION( "and it should update every cycle" ) {
                    Verify( Method( gameStateDouble, update ) ).Exactly( 100_Times );
                }
            }
        }

        SECTION( "with peak load" ) {
            When( Method( gameStateDouble, draw ) ).AlwaysDo(
                [&virtualTime]{ if ( virtualTime == 3 ) virtualTime += 800; }
            );
            When( Method( gameStateDouble, update ) ).AlwaysDo( [&virtualTime](...){ virtualTime++; } );
            subject.run();
            SECTION( "it should draw with a fixed maximum frame rate" ) {
                Verify( Method( gameStateDouble, draw ) ).Exactly( 100_Times );
                SECTION( "and it should update every cycle" ) {
                    Verify( Method( gameStateDouble, update ) ).Exactly( 100_Times );
                }
            }
        }

        SECTION( "with sometimes zero elapsed time" ) {
            std::srand( 42 );
            When( Method( timerDouble, getTime ) ).AlwaysDo(
                [&virtualTime]{ return ( std::rand()&1 ) ? virtualTime : virtualTime++; }
            );
            subject.run();
            SECTION( "it should draw with a fixed maximum frame rate" ) {
                Verify( Method( gameStateDouble, draw ) ).Exactly( 100_Times );
                SECTION( "and it should update every cycle" ) {
                    Verify( Method( gameStateDouble, update ) ).Exactly( 100_Times );
                }
            }
        }

        SECTION( "with moderate calculation stress" ) {
            When( Method( gameStateDouble, draw ) ).AlwaysDo( [&virtualTime]{ virtualTime += 8; } );
            When( Method( gameStateDouble, update ) ).AlwaysDo( [&virtualTime](...){ virtualTime++; } );
            subject.run();
            SECTION( "it should begin to skip frames" ) {
                Verify( Method( gameStateDouble, draw ) ).AtLeast( 85_Times );
                SECTION( "but it should update every cycle" ) {
                    Verify( Method( gameStateDouble, update ) ).Exactly( 100_Times );
                }
            }
        }

        SECTION( "with much calculation stress" ) {
            When( Method( gameStateDouble, draw ) ).AlwaysDo( [&virtualTime]{ virtualTime += 200; } );
            When( Method( gameStateDouble, update ) ).AlwaysDo( [&virtualTime](...){ virtualTime++; } );
            subject.run();
            SECTION( "it should still try to draw" ) {
                Verify( Method( gameStateDouble, draw ) ).AtLeast( 5_Times );
                SECTION( "and it should try to update many cycles" ) {
                    Verify( Method( gameStateDouble, update ) ).AtLeast( 40_Times );
                }
            }
        }
    }
}

TEST_CASE( "LeviathanDevice exit status" ) {
    leviathan::LeviathanDevice subject;
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\nscreen_x=32\nscreen_y=20\n" );

    SECTION( "it is 0 if everything went well" ) {
        REQUIRE( 0 == subject.exitStatus() );
        subject.init( configFileName );
        REQUIRE( 0 == subject.exitStatus() );
    }
}

TEST_CASE( "LeviathanDevice input event handling" ) {
    Testhelper testhelper;
    TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock subject;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\nmax_fps=100\nscreen_x=5\nscreen_y=5\n" );
    subject.init( configFileName );

    SECTION( "keyboard used" ) {
        subject.sendKeyboardEvent( irr::KEY_KEY_Z, true, false, false );
        subject.sendKeyboardEvent( irr::KEY_KEY_J, true, false, true );
        subject.Keyboard().update();
        subject.sendKeyboardEvent( irr::KEY_KEY_Z, true, false, false );
        subject.sendKeyboardEvent( irr::KEY_KEY_J, false, true, true );
        REQUIRE( subject.Keyboard().isKeyDown( irr::KEY_KEY_Z ) );
        REQUIRE( subject.Keyboard().wasKeyDown( irr::KEY_KEY_Z ) );
        REQUIRE( subject.Keyboard().hasKeyJustBeenReleased( irr::KEY_KEY_J ) );
        REQUIRE( subject.Keyboard().isCtrlDown() );
        REQUIRE( subject.Keyboard().wasCtrlDown() );
        REQUIRE( subject.Keyboard().isShiftDown() );
        REQUIRE_FALSE( subject.Keyboard().wasShiftDown() );
    }

    SECTION( "mouse used" ) {
        subject.sendMouseEvent( leviathan::input::Mouse::Button::MIDDLE, true, 12, 34, -2.4f );
        subject.Mouse().update();
        subject.sendMouseEvent( leviathan::input::Mouse::Button::MIDDLE, false, 12, 34, 0.0f );
        subject.sendMouseEvent( leviathan::input::Mouse::Button::RIGHT, true, 13, 33, 1.2f );
        REQUIRE_FALSE( subject.Mouse().isMMBDown() );
        REQUIRE( subject.Mouse().isRMBDown() );
        REQUIRE( subject.Mouse().getPosition() == irr::core::position2di(13, 33) );
        REQUIRE( subject.Mouse().getLastPosition() == irr::core::position2di(12, 34) );
        REQUIRE( subject.Mouse().getWheelDelta() == Approx( 1.2f ) );
    }

    SECTION( "gui used" ) {
        // TODO refactor as soon as we have proper GUI management implemented

        subject.sendGUIEvent( nullptr, irr::gui::EGET_ELEMENT_FOCUSED );
    }
}
