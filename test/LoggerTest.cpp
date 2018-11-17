#include <catch.hpp>
#include "irrlicht.h"
#include <cstdint>
#include "leviathan.h"
#include "helpers/Testhelper.h"

TEST_CASE("Logger: init") {
    Testhelper testhelper;
    const irr::io::path logFileName = "testlogfile.log";
    leviathan::core::Logger sample(
        testhelper.getFileSystem(),
        testhelper.getGraphicEngine()->getTimer(),
        logFileName,
        leviathan::core::Logger::Level::INFO
    );
    sample.flush();

    SECTION("it creates a logfile") {
        REQUIRE(testhelper.existFile(logFileName));

        uint32_t size = testhelper.getFileSize(logFileName);

        SECTION("by overwriting an existing logfile") {
            leviathan::core::Logger subject(
                    testhelper.getFileSystem(),
                    testhelper.getGraphicEngine()->getTimer(),
                    logFileName,
                    leviathan::core::Logger::Level::INFO
            );
            subject.flush();
            uint32_t newSize = testhelper.getFileSize(logFileName);
            REQUIRE(newSize == size);
        }
        SECTION("by appending to an existing logfile") {
            leviathan::core::Logger subject(
                    testhelper.getFileSystem(),
                    testhelper.getGraphicEngine()->getTimer(),
                    logFileName,
                    leviathan::core::Logger::Level::INFO,
                    true
            );
            subject.flush();
            uint32_t newSize = testhelper.getFileSize(logFileName);
            REQUIRE(newSize == size * 2);
        }
        SECTION("and writes the global logging level into it") {
            irr::core::stringc content = testhelper.readFile(logFileName);
            REQUIRE(content.find("] LogLevel: Info") > -1);
        }
    }
    SECTION("multiple logfiles may exist") {
        const irr::io::path anotherLogFileName = "testlogfile2.log";
        leviathan::core::Logger sample2(
                testhelper.getFileSystem(),
                testhelper.getGraphicEngine()->getTimer(),
                anotherLogFileName,
                leviathan::core::Logger::Level::INFO
        );
        REQUIRE(testhelper.existFile(logFileName));
        REQUIRE(testhelper.existFile(anotherLogFileName));
    }
}

TEST_CASE("Logger: logging") {
    Testhelper testhelper;
    const irr::io::path logFileName = "testlogfile.log";

    SECTION("it writes text into the logfile") {
        leviathan::core::Logger subject(
                testhelper.getFileSystem(),
                testhelper.getGraphicEngine()->getTimer(),
                logFileName,
                leviathan::core::Logger::Level::INFO
        );
        subject.text = "Kilroy wuz here";
        subject.write();
        subject.flush();
        irr::core::stringc content = testhelper.readFile(logFileName);
        REQUIRE(content.find("] Kilroy wuz here") > -1);

        SECTION("with special characters") {
            subject.text = "german umlauts: äöüß, some other things: >_%&$§?!@|";
            subject.write();
            subject.flush();
            content = testhelper.readFile(logFileName);
            REQUIRE(content.find("äöüß") > -1);
            REQUIRE(content.find(">_%&$§?!@|") > -1);
        }
        SECTION("over multiple lines") {
            subject.text = "one line.";
            subject.write();
            subject.text = "another line.";
            subject.write();
            subject.flush();
            content = testhelper.readFile(logFileName);
            int32_t firstIndex = content.find("line.");
            REQUIRE(firstIndex > -1);
            REQUIRE(content.find("line.", static_cast<uint32_t>(firstIndex) + 1) > -1);
        }
    }
    SECTION("it handles different logLevels") {
        leviathan::core::Logger subject(
            testhelper.getFileSystem(),
            testhelper.getGraphicEngine()->getTimer(),
            logFileName,
            leviathan::core::Logger::Level::DETAIL
        );
        subject.text = "a line just for information";
        subject.write(leviathan::core::Logger::Level::INFO);
        subject.text = "a line full of details";
        subject.write(leviathan::core::Logger::Level::DETAIL);
        subject.text = "a line for debugging";
        subject.write(leviathan::core::Logger::Level::DEBUG);
        subject.text = "a line hopefully never ever written";
        subject.write(leviathan::core::Logger::Level::ALL);
        subject.flush();
        irr::core::stringc content = testhelper.readFile(logFileName);
        REQUIRE(content.find("information") > -1);
        REQUIRE(content.find("details") > -1);
        REQUIRE_FALSE(content.find("debugging") > -1);
        REQUIRE_FALSE(content.find("never ever") > -1);
    }
}
