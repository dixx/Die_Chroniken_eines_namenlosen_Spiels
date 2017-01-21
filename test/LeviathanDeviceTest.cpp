#include "catch.hpp"
#include "leviathan.h"

TEST_CASE( "LeviathanDevice" ) {
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
    SECTION( "it can read a config file" ) {
        // SECTION( "it uses some of the values in the graphic engine" ) {} // TODO own tests
        // SECTION( "it can read user defined sections" ) {} // TODO own tests
    }
}
