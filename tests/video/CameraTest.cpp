#include "../../source/Leviathan/video/Camera.h"
#include "../../source/Leviathan/core/Configuration.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"

using namespace fakeit;

TEST_CASE("Camera", "[integration]") {
    Mock<irr::scene::ISceneManager> sceneManagerSpy(*(TestHelper::graphicEngine()->getSceneManager()));
    irr::scene::ICameraSceneNode* cameraSample = sceneManagerSpy.get().addCameraSceneNode();
    When(Method(sceneManagerSpy, addCameraSceneNode)).AlwaysReturn(cameraSample);

    SECTION("is created with settings from configuration") {
        const char* configFileName = "testconfigfile.ini";
        TestHelper::writeFile(configFileName, "camera:\n  far_value: 123.0\nvideo:\n  screen_x: 4\n  screen_y: 2\n");
        leviathan::core::Configuration config(configFileName);
        leviathan::video::Camera subject(&sceneManagerSpy.get(), config);

        Verify(Method(sceneManagerSpy, addCameraSceneNode)).Exactly(Once);
        REQUIRE(cameraSample->getFarValue() == Approx(123.0f));
    }
}
