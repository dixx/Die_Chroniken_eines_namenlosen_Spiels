#include "Ground.h"
#include "../video/MeshHelper.h"

namespace leviathan {
    namespace world {
        Ground::Ground(irr::scene::ISceneManager* sceneManager) : sceneManager_(sceneManager) {}

        void Ground::add(const GroundTileConfiguration& tileConfig) {
            irr::scene::IMesh* mesh = sceneManager_->getMesh(tileConfig.fileName);
            mesh->grab();
            transformMesh(mesh, tileConfig);
            video::MeshHelper::pushMeshToVRAM(mesh);
            groundTile_ = sceneManager_->addMeshSceneNode(mesh);
            mesh->drop();
            groundTile_->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            // groundTile_->setVisible(false);
        }

        Ground::~Ground() {
            if (groundTile_) unload();
        }

        void Ground::unload() {
            video::MeshHelper::removeMeshFromVRAM(groundTile_->getMesh(), sceneManager_->getVideoDriver());
            groundTile_->remove();
            groundTile_ = nullptr;
            sceneManager_->getMeshCache()->clearUnusedMeshes();
        }

        void Ground::transformMesh(irr::scene::IMesh* mesh, const GroundTileConfiguration& tileConfig) {
            irr::core::matrix4 matrix = irr::core::matrix4();
            matrix.setTranslation(tileConfig.position.toVector());
            matrix.setRotationDegrees(tileConfig.rotation.toVector());
            matrix.setScale(tileConfig.scale.toVector());
            sceneManager_->getMeshManipulator()->transform(mesh, matrix);
            sceneManager_->getMeshManipulator()->recalculateNormals(mesh, true);
        }
    }
}
