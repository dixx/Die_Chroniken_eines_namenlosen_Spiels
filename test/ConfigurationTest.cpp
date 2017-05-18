#include <catch.hpp>
#include "leviathan.h"
#include "Testhelper.h"

// TODO
// - enum values are allowed (only /[A-Z0-9_]/)
// - boolean values are `true` and `false`
// - integer values can be positive or negative
// - float values may not have leading zeroes, can be positive or negative, and must have a `.` in them

TEST_CASE( "Configuration: it provides a default object" ) {
    leviathan::core::Configuration subject;
    REQUIRE( subject.getGraphicEngineParams().DriverType == irr::video::EDT_NULL );
    REQUIRE( subject.getGraphicEngineParams().LoggingLevel == irr::ELL_WARNING );
}

TEST_CASE( "Configuration: read values" ) {
    Testhelper testhelper;
    const irr::io::path configFileName = "testconfigfile.ini";
    leviathan::core::Configuration subject;

    SECTION( "all relevant values can be read" ) {
        irr::core::stringc content = "[general]\n";
        content += "# logging levels: INFO, DETAIL, DEBUG, ALL\n";
        content += "logging_level = ALL\n";
        content += "\n";
        content += "[video]\n";
        content += "screen_x = 1366\n";
        content += "screen_y = 768\n";
        content += "# color depth: 16bit, 32bit\n";
        content += "color_depth = 32\n";
        content += "fullscreen = true\n";
        content += "# drivers: DIRECT3D8, DIRECT3D9, OPENGL, SOFTWARE (slow!), BURNINGSVIDEO, NULL\n";
        content += "driver = OPENGL\n";
        content += "\n";
        content += "[camera]\n";
        content += "far_value = 300.0\n";
        testhelper.writeFile( configFileName, content );
        subject.readFromFile( configFileName, testhelper.getFileSystem() );
        REQUIRE( subject.getGraphicEngineParams().WindowSize.Width == 1366 );
        REQUIRE( subject.getGraphicEngineParams().WindowSize.Height == 768 );
        REQUIRE( subject.getGraphicEngineParams().Bits == 32 );
        REQUIRE( subject.getGraphicEngineParams().Fullscreen == true );
        REQUIRE( subject.getGraphicEngineParams().DriverType == irr::video::EDT_OPENGL );
        REQUIRE( subject.getFarValue() == Approx( 300.0f ) );
        REQUIRE( subject.getLoggingLevel() == leviathan::core::Logger::Level::ALL );

        SECTION( "reading again overwrites changes" ) {
            testhelper.writeFile( configFileName, "[video]\ncolor_depth=42\n" );
            subject.readFromFile( configFileName, testhelper.getFileSystem() );
            REQUIRE( subject.getGraphicEngineParams().Bits == 42 );
        }
    }
    SECTION( "it uses default values" ) {
        SECTION( "if keys are missing" ) {
            testhelper.writeFile( configFileName, "" );
            subject.readFromFile( configFileName, testhelper.getFileSystem() );
            REQUIRE( subject.getGraphicEngineParams().WindowSize.Width == 800 );
            REQUIRE( subject.getGraphicEngineParams().WindowSize.Height == 600 );
            REQUIRE( subject.getGraphicEngineParams().Bits == 16 );
            REQUIRE( subject.getGraphicEngineParams().Fullscreen == false );
            REQUIRE( subject.getGraphicEngineParams().DriverType == irr::video::EDT_SOFTWARE );
            REQUIRE( subject.getFarValue() == Approx( 300.0f ) );
            REQUIRE( subject.getLoggingLevel() == leviathan::core::Logger::Level::INFO );
        }
        SECTION( "if file is missing" ) {
            subject.readFromFile( "totally_nonexisting_file", testhelper.getFileSystem() );
            REQUIRE( subject.getGraphicEngineParams().Bits == 16 );
        }
    }
    SECTION( "# and ; are valid comment indicators" ) {
        testhelper.writeFile( configFileName, "[test_section]\n;test_value=1\n#test_value=2\ntest_value=3\n" );
        subject.readFromFile( configFileName, testhelper.getFileSystem() );
        REQUIRE( subject.getInt( "test_section", "test_value" ) == 3 );
    }
    SECTION( "erroneous section will be ignored" ) {
        testhelper.writeFile( configFileName, "[s 1]\nv=42\n[s\n2]\nv=42\n[s3]v=42\n[[s4]s4]\nv=42\n[s]5]\nv=42\n" );
        subject.readFromFile( configFileName, testhelper.getFileSystem() );
        REQUIRE( subject.getInt( "s1", "v" ) == 0 );
        REQUIRE( subject.getInt( "s2", "v" ) == 0 );
        REQUIRE( subject.getInt( "s3", "v" ) == 0 );
        REQUIRE( subject.getInt( "s4", "v" ) == 0 );
        REQUIRE( subject.getInt( "s]5", "v" ) == 42 );
    }
    SECTION( "erroneous key-value-pair will be ignored" ) {
        testhelper.writeFile( configFileName, "[s]\nv 1=42\nv2 == 42\nv3 42\nv4=\nv[5=42\n" );
        subject.readFromFile( configFileName, testhelper.getFileSystem() );
        REQUIRE( subject.getInt( "s", "v1" ) == 0 );
        REQUIRE( subject.getInt( "s", "v2" ) == 0 );
        REQUIRE( subject.getInt( "s", "v3" ) == 0 );
        REQUIRE( subject.getInt( "s", "v4" ) == 0 );
        REQUIRE( subject.getInt( "s", "v[5" ) == 42 );
    }
}

TEST_CASE( "Configuration: write values" ) {
    SECTION( "it writes back all sections and values" ) {}
    SECTION( "it writes back comments and blank lines" ) {}
    SECTION( "inline comments and white spaces are removed during write" ) {}
    SECTION( "it adds missing values with defaults" ) {}
}
