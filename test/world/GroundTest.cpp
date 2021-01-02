#include "../../source/Leviathan/world/Ground.h"
#include "../helpers/TestHelper.h"
#include "catch.hpp"
#include "fakeit.hpp"
#include "irrlicht.h"

using namespace fakeit;

#define getMeshArgs irr::scene::IAnimatedMesh*(const irr::io::path&)

TEST_CASE("Ground", "[integration]") {
    Mock<irr::scene::ISceneManager> sceneManagerSpy(*(TestHelper::graphicEngine()->getSceneManager()));
    sceneManagerSpy.get().addSphereMesh("path/to/meshFile");  // add a test mesh to avoid getting a nullptr
    leviathan::world::Ground subject(&sceneManagerSpy.get());

    SECTION("add") {
        SECTION("single ground tile") {
            leviathan::world::GroundTileConfiguration groundTileConfig(
                {"path/to/meshFile", {1, 2, 3}, {4, 5, 6}, {7, 8, 9}});
            subject.add(groundTileConfig);

            // FIXME: spying on the mesh results in strange errors

            // FIXME: for whatever reson these calls are not recognized by FakeIt:
            // Verify(OverloadedMethod(sceneManagerSpy, getMesh, getMeshArgs)).Exactly(Once);
            // Verify(Method(sceneManagerSpy, addMeshSceneNode)).Exactly(Once);
        }

        SECTION("multiple ground tiles") {}
    }

    SECTION("unload all ground tiles") {}
}
