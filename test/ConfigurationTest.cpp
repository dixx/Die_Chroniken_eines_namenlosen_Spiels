#include "catch.hpp"
#include "leviathan.h"
#include "Testhelper.h"

TEST_CASE( "Configuration: INI file rules") {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    leviathan::core::Configuration subject( testhelper.getFileSystem() );

    SECTION( "# and ; are valid comment indicators" ) {}
    SECTION( "comments and blank lines are written back" ) {}
    SECTION( "inline comments and white spaces are removed during write" ) {}
    // - string values must have ""
    // - enum values are allowed (only /[\w_]/)
    // - boolean values are `true` and `false`
    // - float values may not have leading zeroes, and must have a `.` in them
    SECTION( "erroneous section will be logged and ignored" ) {
        SECTION( "too many [" ) {}
        SECTION( "too many ]" ) {}
        SECTION( "too few [" ) {}
        SECTION( "too few ]" ) {}
        SECTION( "section name has invalid chars" ) {}
    }
    SECTION( "erroneous key-value-pair will be logged and ignored" ) {
        SECTION( "= missing" ) {}
        SECTION( "more than one =" ) {}
        SECTION( "key missing" ) {}
        SECTION( "value missing" ) {}
        SECTION( "key has invalid chars" ) {}
    }
}

TEST_CASE( "Configuration: read values" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    leviathan::core::Configuration subject( testhelper.getFileSystem() );

    SECTION( "all relevant values can be read" ) {}
    SECTION( "it uses some of the values in the graphic engine" ) {}
    SECTION( "it can read user defined sections" ) {}
    SECTION( "it uses default values" ) {
        SECTION( "if file is missing" ) {}
        SECTION( "if keys are missing" ) {}
    }
    SECTION( "reading same file again overwrites changes" ) {}
}

TEST_CASE( "Configuration: write values" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    leviathan::core::Configuration subject( testhelper.getFileSystem() );

    SECTION( "it writes back all sections and values" ) {}
    SECTION( "it writes back the user defined sections that were read before" ) {}
    SECTION( "it creates the file if missing" ) {}
}
