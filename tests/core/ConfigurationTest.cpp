#include "../../src/Leviathan/core/Configuration.h"
#include "../../src/Leviathan/core/Logger.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "irrlicht.h"
#include <string>

TEST_CASE("Configuration: read values", "[unit]") {
    const char* configFileName = "testconfigfile.yaml";

    SECTION("all relevant values can be read") {
        std::string content = "---\n"
                              "general:\n"
                              "  # logging levels: INFO, DETAIL, DEBUG, ALL\n"
                              "  logging_level: ALL\n"
                              "video:\n"
                              "  screen_x: 1366\n"
                              "  screen_y: 768\n"
                              "  # color depth: 16bit, 32bit\n"
                              "  color_depth: 32\n"
                              "  fullscreen: true\n"
                              "  # drivers: DIRECT3D8, DIRECT3D9, OPENGL, SOFTWARE (slow!), BURNINGSVIDEO, NULL\n"
                              "  driver: DIRECT3D8\n"
                              "  max_fps: 42\n"
                              "camera:\n"
                              "  far_value: 600.0\n";
        TestHelper::writeFile(configFileName, content.c_str());
        leviathan::core::Configuration subject(configFileName);
        REQUIRE(subject.getGraphicEngineParams().WindowSize.Width == 1366);
        REQUIRE(subject.getGraphicEngineParams().WindowSize.Height == 768);
        REQUIRE(subject.getGraphicEngineParams().Bits == 32);
        REQUIRE(subject.getGraphicEngineParams().Fullscreen == true);
        REQUIRE(subject.getGraphicEngineParams().DriverType == irr::video::EDT_DIRECT3D8);
        REQUIRE(subject.getFarValue() == Approx(600.0f));
        REQUIRE(subject.getLoggingLevel() == leviathan::core::Logger::Level::ALL);
        REQUIRE(subject.getMaxFPS() == 42);
        REQUIRE(subject.getScreenSize().w == 1366);
        REQUIRE(subject.getScreenSize().h == 768);

        SECTION("reading again overwrites changes") {
            TestHelper::writeFile(configFileName, "---\nvideo:\n  screen_x: 1024\n");
            subject.readFromFile(configFileName);
            REQUIRE(subject.getGraphicEngineParams().WindowSize.Width == 1024);
        }
    }
}

TEST_CASE("Configuration: default values", "[unit]") {
    const char* configFileName = "testconfigfile.yaml";

    SECTION("on unsuccessfull config file read") {
        leviathan::core::Configuration subject("");
        REQUIRE(subject.getGraphicEngineParams().WindowSize.Width == 800);
        REQUIRE(subject.getGraphicEngineParams().WindowSize.Height == 600);
        REQUIRE(subject.getGraphicEngineParams().DriverType == irr::video::EDT_OPENGL);
        REQUIRE(subject.getGraphicEngineParams().Bits == 16);
        REQUIRE(subject.getGraphicEngineParams().Fullscreen == false);
        REQUIRE(subject.getFarValue() == Approx(300.0f));
        REQUIRE(subject.getLoggingLevel() == leviathan::core::Logger::Level::INFO);
        REQUIRE(subject.getMaxFPS() == 60);
        REQUIRE(subject.getScreenSize().w == 800);
        REQUIRE(subject.getScreenSize().h == 600);
    }
    SECTION("if keys or sections are unknown") {
        std::string content = "---\n"
                              "general:\n"
                              "  logging_level: who_knows\n"
                              "video:\n"
                              "  color_depth: 24\n"
                              "videooo:\n"
                              "  driver: SOFTWARE\n";
        TestHelper::writeFile(configFileName, content.c_str());
        leviathan::core::Configuration subject(configFileName);
        REQUIRE(subject.getLoggingLevel() == leviathan::core::Logger::Level::INFO);
        REQUIRE(subject.getGraphicEngineParams().Bits == 16);
        REQUIRE(subject.getGraphicEngineParams().DriverType == irr::video::EDT_OPENGL);
    }
}

TEST_CASE("Configuration: write values", "[.]") {
    SECTION("it writes back all sections and values") {}
    SECTION("it writes back comments and blank lines") {}
    SECTION("inline comments and white spaces are removed during write") {}
    SECTION("it adds missing values with defaults") {}
}
