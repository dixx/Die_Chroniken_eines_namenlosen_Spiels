#include "catch.hpp"
#include "leviathan.h"

irr::IrrlichtDevice* createGraphicEngine()
{
    irr::SIrrlichtCreationParameters params;
    params.DriverType = irr::video::EDT_NULL;
    params.LoggingLevel = irr::ELL_WARNING;
    return irr::createDeviceEx( params );
}

irr::core::stringc readFile( irr::io::path fileName, irr::io::IFileSystem* fileSystem )
{
    irr::io::IReadFile* file = fileSystem->createAndOpenFile( fileName );
    irr::u32 size = (irr::u32)file->getSize();
    irr::u8 buffer[ size + 4 ];
    file->read( &buffer, size );
    file->drop();
    return (irr::core::stringc)buffer;
}

irr::u32 getFileSize( irr::io::path fileName, irr::io::IFileSystem* fileSystem )
{
    irr::io::IReadFile* file = fileSystem->createAndOpenFile( fileName );
    irr::u32 size = (irr::u32)file->getSize();
    file->drop();
    return size;
}

TEST_CASE( "Logger: init" ) {
    irr::IrrlichtDevice* graphicEngine = createGraphicEngine();
    irr::io::IFileSystem* fileSystem = graphicEngine->getFileSystem();
    const irr::io::path logFileName = "testlogfile.log";
    leviathan::core::Logger sample( fileSystem, graphicEngine->getTimer(), logFileName, leviathan::core::Logger::INFO );
    sample.flush();

    SECTION( "it creates a logfile" ) {
        REQUIRE( fileSystem->existFile( logFileName ) );

        irr::u32 size = getFileSize( logFileName, fileSystem );

        SECTION( "by overwriting an existing logfile" ) {
            leviathan::core::Logger subject(
                    fileSystem,
                    graphicEngine->getTimer(),
                    logFileName,
                    leviathan::core::Logger::INFO
            );
            subject.flush();
            irr::u32 newSize = getFileSize( logFileName, fileSystem );
            REQUIRE( newSize == size );
        }
        SECTION( "by appending to an existing logfile" ) {
            leviathan::core::Logger subject(
                    fileSystem,
                    graphicEngine->getTimer(),
                    logFileName,
                    leviathan::core::Logger::INFO,
                    true
            );
            subject.flush();
            irr::u32 newSize = getFileSize( logFileName, fileSystem );
            REQUIRE( newSize == size * 2 );
        }
        SECTION( "and writes the global logging level into it" ) {
            irr::core::stringc content = readFile( logFileName, fileSystem );
            REQUIRE( content.find("] LogLevel: Info") > -1 );
        }
    }
    SECTION( "multiple logfiles may exist" ) {
        const irr::io::path anotherLogFileName = "testlogfile2.log";
        leviathan::core::Logger sample2(
                fileSystem,
                graphicEngine->getTimer(),
                anotherLogFileName,
                leviathan::core::Logger::INFO
        );
        REQUIRE( fileSystem->existFile( logFileName ) );
        REQUIRE( fileSystem->existFile( anotherLogFileName ) );
    }

    graphicEngine->drop();
}

TEST_CASE( "Logger: logging" ) {
    irr::IrrlichtDevice* graphicEngine = createGraphicEngine();
    irr::io::IFileSystem* fileSystem = graphicEngine->getFileSystem();
    const irr::io::path logFileName = "testlogfile.log";

    SECTION( "it writes text into the logfile" ) {
        leviathan::core::Logger subject(
                fileSystem,
                graphicEngine->getTimer(),
                logFileName,
                leviathan::core::Logger::INFO
        );
        subject.text = "Kilroy wuz here";
        subject.write();
        subject.flush();
        irr::core::stringc content = readFile( logFileName, fileSystem );
        REQUIRE( content.find( "] Kilroy wuz here" ) > -1 );

        SECTION( "with special characters" ) {
            subject.text = "german umlauts: äöüß, some other things: >_%&$§?!@|";
            subject.write();
            subject.flush();
            content = readFile( logFileName, fileSystem );
            REQUIRE( content.find( "äöüß" ) > -1 );
            REQUIRE( content.find( ">_%&$§?!@|" ) > -1 );
        }
        SECTION( "over multiple lines" ) {
            subject.text = "one line.";
            subject.write();
            subject.text = "another line.";
            subject.write();
            subject.flush();
            content = readFile( logFileName, fileSystem );
            irr::s32 firstIndex = content.find( "line." );
            REQUIRE( firstIndex > -1 );
            REQUIRE( content.find( "line.", (irr::u32)firstIndex + 1 ) > -1 );
        }
    }
    SECTION( "it handles different logLevels" ) {
        leviathan::core::Logger subject( fileSystem, graphicEngine->getTimer(), logFileName, leviathan::core::Logger::DETAIL );
        subject.text = "a line just for information";
        subject.write( leviathan::core::Logger::INFO );
        subject.text = "a line full of details";
        subject.write( leviathan::core::Logger::DETAIL );
        subject.text = "a line for debugging";
        subject.write( leviathan::core::Logger::DEBUG );
        subject.text = "a line hopefully never ever written";
        subject.write( leviathan::core::Logger::ALL );
        subject.flush();
        irr::core::stringc content = readFile( logFileName, fileSystem );
        REQUIRE( content.find( "information" ) > -1 );
        REQUIRE( content.find( "details" ) > -1 );
        REQUIRE_FALSE( content.find( "debugging" ) > -1 );
        REQUIRE_FALSE( content.find( "never ever" ) > -1 );
    }

    graphicEngine->drop();
}
