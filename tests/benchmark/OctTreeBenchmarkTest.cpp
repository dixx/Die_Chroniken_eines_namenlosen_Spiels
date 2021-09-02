#include "../../src/Leviathan/core/Randomizer.h"
#include "../../src/Leviathan/world/Ground.h"
#include "../helpers/TestHelper.h"
#include "IMeshCache.h"
#include "IMeshSceneNode.h"
#include "ISceneCollisionManager.h"
#include "ISceneManager.h"
#include "IrrlichtDevice.h"
#include "catch.hpp"
#include "irrTypes.h"
#include <cstdint>
#include <iostream>
#include <vector>

TEST_CASE("OctTreeBenchmark", "[benchmark]") {
    leviathan::core::Randomizer rnd;
    irr::IrrlichtDevice* device = TestHelper::graphicEngine();
    rnd.start(device->getTimer()->getRealTime());
    irr::scene::ISceneManager* smgr = device->getSceneManager();
    smgr->clear();
    smgr->getMeshCache()->clearUnusedMeshes();
    smgr->addHillPlaneMesh("path/to/meshFile", irr::core::dimension2df(10.f, 10.f), irr::core::dimension2du(1000, 1000),
        0, 100.f, irr::core::dimension2df(20.f, 33.f));
    irr::scene::IMesh* mesh = smgr->getMesh("path/to/meshFile");
    irr::scene::IMeshSceneNode* node = smgr->addMeshSceneNode(mesh);
    node->setVisible(true);
    irr::u32 startTime = 0;
    irr::u32 endTime = 0;
    irr::core::vector3df collisionPoint;
    irr::core::triangle3df collisionTriangle;
    irr::core::line3df ray;
    uint32_t raycastCount = 1000;
    uint32_t vertexCount = mesh->getMeshBuffer(0)->getVertexCount();
    std::cout << "#Polys: " << vertexCount << ", raycast: " << raycastCount << " times" << std::endl;
    std::vector<uint32_t> minPolys({vertexCount, vertexCount / 2, vertexCount / 4, vertexCount / 8, vertexCount / 16,
        vertexCount / 64, vertexCount / 512, 32, 4});
    float min_x = node->getMesh()->getBoundingBox().MinEdge.X;
    float min_y = node->getMesh()->getBoundingBox().MinEdge.Y;
    float min_z = node->getMesh()->getBoundingBox().MinEdge.Z;
    float max_x = node->getMesh()->getBoundingBox().MaxEdge.X;
    float max_y = node->getMesh()->getBoundingBox().MaxEdge.Y;
    float max_z = node->getMesh()->getBoundingBox().MaxEdge.Z;

    for (auto minPolyCount : minPolys) {
        std::cout << minPolyCount << " minPoly: ";
        irr::scene::ITriangleSelector* selector = node->getTriangleSelector();
        if (selector) {
            node->setTriangleSelector(0);
        }
        selector = smgr->createOctreeTriangleSelector(node->getMesh(), node, static_cast<irr::s32>(minPolyCount));
        node->setTriangleSelector(selector);
        selector->drop();
        startTime = device->getTimer()->getRealTime();
        for (uint32_t i = 0; i < raycastCount; ++i) {
            float x = rnd.getFloat(min_x, max_x);
            float z = rnd.getFloat(min_z, max_z);
            ray.setLine(x, min_y, z, x, max_y, z);
            smgr->getSceneCollisionManager()->getSceneNodeAndCollisionPointFromRay(
                ray, collisionPoint, collisionTriangle);
        }
        endTime = device->getTimer()->getRealTime();
        std::cout << "selector searched within " << endTime - startTime << "ms." << std::endl;
    }
}
