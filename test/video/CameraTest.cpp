#include "../../source/Leviathan/video/Camera.h"
#include "../../source/Leviathan/core/Configuration.h"
#include "../helpers/ICameraSceneNodeMock.hpp"
#include "../helpers/Testhelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"

using namespace fakeit;

TEST_CASE("Camera", "[unit]") {
    Mock<irr::IrrlichtDevice> graphicDeviceMock;
    Mock<irr::scene::ISceneManager> sceneManagerMock;
    mocks::ICameraSceneNodeMock* cameraMock = new mocks::ICameraSceneNodeMock(nullptr, nullptr, -1);
    cameraMock->grab();
    When(Method(graphicDeviceMock, getSceneManager)).AlwaysReturn(&sceneManagerMock.get());
    When(Method(sceneManagerMock, addCameraSceneNode)).AlwaysReturn(cameraMock);

    SECTION("with default settings") {
        leviathan::video::Camera subject(&graphicDeviceMock.get());

        Verify(Method(sceneManagerMock, addCameraSceneNode)).Exactly(Once);
        REQUIRE(cameraMock->mFarValue == Approx(0.0f));
    }

    SECTION("with settings from configuration") {
        Testhelper testhelper;
        const char* configFileName = "testconfigfile.ini";
        testhelper.writeFile(configFileName, "[camera]\nfar_value=123.0\nscreen_x=4\nscreen_y=2\n");
        leviathan::core::Configuration config(configFileName);
        leviathan::video::Camera subject(&graphicDeviceMock.get(), config);

        Verify(Method(sceneManagerMock, addCameraSceneNode)).Exactly(Once);
        REQUIRE(cameraMock->mFarValue == Approx(123.0f));
    }
}
