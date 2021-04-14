#include "../../src/Leviathan/world/NodeManager.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

TEST_CASE("NodeManager", "[integration]") {
    Mock<irr::scene::ISceneManager> sceneManagerSpy(*(TestHelper::graphicEngine()->getSceneManager()));
    leviathan::world::NodeManager subject(&sceneManagerSpy.get());

    sceneManagerSpy.get().addSphereMesh("path/to/meshFile");  // add a test mesh to avoid getting a nullptr

    SECTION("add 3D objects") {
        subject.add3DNode("path/to/meshFile", {1, 2, 3}, {11, 22, 33}, {4, 5, 6}, {7, 8, 9});
    }

    SECTION("unload all 3d objects") {
        subject.unload();
    }
}
