#include "../../src/Leviathan/world/Collider.h"
#include "../../src/Leviathan/world/NodeUsageBitmasks.h"
#include "../helpers/TestHelper.h"
#include "IMesh.h"
#include "IMeshSceneNode.h"
#include "ISceneCollisionManager.h"
#include "ISceneManager.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include <video/Position2D.h>
#include <world/Collision.h>

using namespace fakeit;

TEST_CASE("Collider", "[integration]") {
    irr::scene::ISceneManager* sceneManager = TestHelper::graphicEngine()->getSceneManager();
    irr::scene::IMesh* mesh = sceneManager->addSphereMesh(
        "path/to/meshFile", 1.f /* radius, center is at 0,0,0 */);  // add a test mesh to avoid getting a nullptr
    irr::scene::IMeshSceneNode* dummyNode = sceneManager->addMeshSceneNode(
        mesh, sceneManager->getSceneNodeFromName("responsiveNodes"), NODE_FLAG_RESPONSIVE);
    Mock<irr::scene::ISceneCollisionManager> spy(*(sceneManager->getSceneCollisionManager()));
    leviathan::world::Collider subject(TestHelper::graphicEngine()->getSceneManager());

    SECTION("getCollisionFromScreenCoordinates") {
        When(Method(spy, getSceneNodeAndCollisionPointFromRay)).AlwaysReturn(dummyNode);
        leviathan::video::Position2D screenCoordinates({0, 0});
        leviathan::world::Collision collision = subject.getCollisionFromScreenCoordinates(screenCoordinates);

        REQUIRE(collision.happened);
    }
}
