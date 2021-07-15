#include "GroundTile.h"
#include "../video/MeshHelper.h"
#include "../video/Vector3DCompatible.h"
#include <EMaterialFlags.h>
#include <IMesh.h>
#include <ISceneManager.h>
#include <matrix4.h>

namespace leviathan {
    namespace world {
        GroundTile::GroundTile(const Node3DConfiguration& tileConfig, irr::scene::ISceneManager* sceneManager)
        : sceneManager_(sceneManager) {
            irr::scene::IMesh* mesh = sceneManager_->getMesh(tileConfig.meshFileName.c_str());
            mesh->grab();
            transformMesh(mesh, tileConfig);
            video::MeshHelper::pushMeshToVRAM(mesh);
            tileNode_ = sceneManager_->addMeshSceneNode(mesh);
            mesh->drop();
            video::Vector3DCompatible position = tileConfig.position;
            // TODO: replace with video::Textures.get
            irr::video::ITexture* texture = sceneManager_->getVideoDriver()->getTexture(
                tileConfig.textureFileName.c_str());
            tileNode_->setMaterialTexture(0, texture);
            tileNode_->setPosition(position.toIrrlichtVector());
            tileNode_->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            tileNode_->setVisible(true);
        }

        GroundTile::~GroundTile() {
            video::MeshHelper::removeMeshFromVRAM(tileNode_->getMesh(), sceneManager_->getVideoDriver());
            tileNode_->remove();
        }

        void GroundTile::setDesiredPostition(const video::Position3D& targetPosition) {
            desiredPosition_ = targetPosition;
        }

        void GroundTile::transformMesh(irr::scene::IMesh* mesh, const Node3DConfiguration& tileConfig) {
            video::Vector3DCompatible offset = tileConfig.offset;
            video::Vector3DCompatible rotation = tileConfig.rotation;
            video::Vector3DCompatible scale = tileConfig.scale;
            irr::core::matrix4 matrix = irr::core::matrix4();
            matrix.setTranslation(offset.toIrrlichtVector());
            matrix.setRotationDegrees(rotation.toIrrlichtVector());
            matrix.setScale(scale.toIrrlichtVector());
            sceneManager_->getMeshManipulator()->transform(mesh, matrix);
            sceneManager_->getMeshManipulator()->recalculateNormals(mesh, true);
        }
    }
}
