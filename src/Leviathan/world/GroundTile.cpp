#include "GroundTile.h"
#include "../video/MeshHelper.h"
#include "../video/Textures.h"
#include "../video/Vector3DCompatible.h"
#include "IMeshManipulator.h"
#include "IMeshSceneNode.h"
#include "ITriangleSelector.h"
#include "IVideoDriver.h"
#include "NodeUsageBitmasks.h"
#include <EMaterialFlags.h>
#include <IMesh.h>
#include <ISceneManager.h>
#include <matrix4.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        GroundTile::GroundTile(
            const Node3DConfiguration& tileConfig, video::Textures& textures, irr::scene::ISceneManager* sceneManager)
        : mTextures(textures), mSceneManager(sceneManager) {
            irr::scene::IMesh* mesh = mSceneManager->getMesh(tileConfig.meshFileName.c_str());
            transformMesh(mesh, tileConfig);
            video::MeshHelper::pushMeshToVRAM(mesh);
            mTileNode = mSceneManager->addMeshSceneNode(mesh);
            mTileNode->setID(NODE_FLAG_WALKABLE + NODE_FLAG_RESPONSIVE);
            mTileNode->setParent(mSceneManager->getSceneNodeFromName("walkableNodes"));
            video::Position3DCompatible position = tileConfig.position;
            mTileNode->setPosition(position.toIrrlichtVector());
            defineAppearance(tileConfig.textureFileName.c_str());
            addTriangleSelector();
        }

        GroundTile::~GroundTile() {
            video::MeshHelper::removeMeshFromVRAM(mTileNode->getMesh(), mSceneManager->getVideoDriver());
            mTileNode->remove();
        }

        void GroundTile::setDesiredPostition(const video::Position3D& targetPosition) {
            mDesiredPosition = targetPosition;
        }

        void GroundTile::transformMesh(irr::scene::IMesh* mesh, const Node3DConfiguration& tileConfig) {
            video::Vector3DCompatible offset = tileConfig.offset;
            video::Rotation3DCompatible rotation = tileConfig.rotation;
            video::Scale3DCompatible scale = tileConfig.scale;
            irr::core::matrix4 matrix = irr::core::matrix4();
            matrix.setTranslation(offset.toIrrlichtVector());
            matrix.setRotationDegrees(rotation.toIrrlichtVector());
            matrix.setScale(scale.toIrrlichtVector());
            mSceneManager->getMeshManipulator()->transform(mesh, matrix);
            mSceneManager->getMeshManipulator()->recalculateNormals(mesh, true);
        }

        void GroundTile::defineAppearance(const char* textureFileName) {
            irr::video::ITexture* texture = mTextures.get(textureFileName);
            mTileNode->setMaterialTexture(0, texture);
            mTileNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            mTileNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
            mTileNode->setMaterialType(irr::video::EMT_SOLID);
            mTileNode->setVisible(true);
        }

        void GroundTile::addTriangleSelector() {
            irr::scene::ITriangleSelector* selector = mSceneManager->createOctreeTriangleSelector(
                mTileNode->getMesh(), mTileNode, 900);  // TODO find a good way to calculate Polys per Node
            mTileNode->setTriangleSelector(selector);
            selector->drop();
        }
    }
}
