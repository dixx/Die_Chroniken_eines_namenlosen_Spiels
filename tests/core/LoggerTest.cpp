#include "../../source/Leviathan/core/Logger.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include <cstdint>
#include <string>

TEST_CASE("Logger", "[unit]") {
    const char* logFileName = "testlogfile.log";

    SECTION("init") {
        SECTION("it creates a logfile") {
            leviathan::core::Logger sample(logFileName, leviathan::core::Logger::Level::INFO);
            REQUIRE(TestHelper::existFile(logFileName));

            uint32_t oldSize = TestHelper::getFileSize(logFileName);

            SECTION("by overwriting an existing logfile") {
                leviathan::core::Logger subject(logFileName, leviathan::core::Logger::Level::INFO);
                REQUIRE(TestHelper::getFileSize(logFileName) == oldSize);
            }

            SECTION("by appending to an existing logfile") {
                leviathan::core::Logger subject(logFileName, leviathan::core::Logger::Level::INFO, true);
                REQUIRE(TestHelper::getFileSize(logFileName) == oldSize * 2);
            }

            SECTION("and writes the global logging level into it") {
                std::string content = TestHelper::readFile(logFileName);
                REQUIRE(content.find("] LogLevel: Info") != std::string::npos);
            }
        }

        SECTION("multiple logfiles may exist") {
            const char* anotherLogFileName = "testlogfile2.log";
            leviathan::core::Logger sample(logFileName, leviathan::core::Logger::Level::INFO);
            leviathan::core::Logger sample2(anotherLogFileName, leviathan::core::Logger::Level::INFO);
            REQUIRE(TestHelper::existFile(logFileName));
            REQUIRE(TestHelper::existFile(anotherLogFileName));
        }
    }

    SECTION("logging") {
        SECTION("it writes text into the logfile") {
            leviathan::core::Logger subject(logFileName, leviathan::core::Logger::Level::INFO);
            subject.text << "Kilroy wuz here";
            subject.write();
            std::string content = TestHelper::readFile(logFileName);
            REQUIRE(content.find("] Kilroy wuz here") != std::string::npos);

            SECTION("with special characters") {
                subject.text << "german umlauts: äöüß, some other things: >_%&$§?!@|";
                subject.write();
                content = TestHelper::readFile(logFileName);
                REQUIRE(content.find("äöüß") != std::string::npos);
                REQUIRE(content.find(">_%&$§?!@|") != std::string::npos);
            }

            SECTION("over multiple lines") {
                subject.text << "one line.";
                subject.write();
                subject.text << "another line.";
                subject.write();
                content = TestHelper::readFile(logFileName);
                uint32_t firstIndex = content.find("line.");
                REQUIRE(firstIndex != std::string::npos);
                REQUIRE(content.find("line.", firstIndex + 1) != std::string::npos);
            }

            SECTION("and clears the text afterwards") {
                subject.text << "usefull information";
                subject.write();
                REQUIRE(subject.text.str().empty());
            }
        }

        SECTION("it handles different logLevels") {
            leviathan::core::Logger subject(logFileName, leviathan::core::Logger::Level::DETAIL);
            subject.text << "a line just for information";
            subject.write(leviathan::core::Logger::Level::INFO);
            subject.text << "a line full of details";
            subject.write(leviathan::core::Logger::Level::DETAIL);
            subject.text << "a line for debugging";
            subject.write(leviathan::core::Logger::Level::DEBUG);
            subject.text << "a line hopefully never ever written";
            subject.write(leviathan::core::Logger::Level::ALL);
            std::string content = TestHelper::readFile(logFileName);
            REQUIRE(content.find("information") != std::string::npos);
            REQUIRE(content.find("details") != std::string::npos);
            REQUIRE(content.find("debugging") == std::string::npos);
            REQUIRE(content.find("never ever") == std::string::npos);
        }
    }
}
