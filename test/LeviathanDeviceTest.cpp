#include "catch.hpp"
#include "leviathan.h"
#include "Testhelper.h"

TEST_CASE( "LeviathanDevice" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    testhelper.writeFile( configFileName, "[video]\ncolor_depth=42\nscreen_x=320\nscreen_y=200\n" );
    leviathan::LeviathanDevice subject;

    SECTION( "it provides a ready-to-use Logger" ) {
        subject.getLogger().text = L"it works!";
        REQUIRE( subject.getLogger().text == L"it works!" );
    }
    SECTION( "it provides a ready-to-use TimeControl" ) {
        leviathan::core::Timer timer( 123 );
        subject.getTimeControl().add( timer );
        timer.start();
        subject.getTimeControl().pause();
        REQUIRE( timer.isPaused() );
    }
    SECTION( "it provides a ready-to-use Configuration" ) {
        REQUIRE( subject.getConfiguration().getGraphicEngineParams().Bits == 16 );
        subject.getConfiguration().readFromFile( configFileName, testhelper.getFileSystem() );
        REQUIRE( subject.getConfiguration().getGraphicEngineParams().Bits == 42 );
    }
    SECTION( "it can write a config file" ) {}
}
