#include "Decoration.h"
#include "../video/MeshHelper.h"
#include "../video/Textures.h"
#include "../video/Vector3DCompatible.h"
#include "IMeshSceneNode.h"
#include "IVideoDriver.h"
#include <IMesh.h>
#include <ISceneManager.h>
#include <world/Node3DConfiguration.h>

namespace leviathan {
    namespace world {
        Decoration::Decoration(
            const Node3DConfiguration& tileConfig, video::Textures& textures, irr::scene::ISceneManager* sceneManager)
        : mTextures(textures), mSceneManager(sceneManager) {
            irr::scene::IMesh* mesh = mSceneManager->getMesh(tileConfig.meshFileName.c_str());
            video::MeshHelper::pushMeshToVRAM(mesh);
            mdecorationNode = mSceneManager->addMeshSceneNode(mesh);
            transformSceneNode(tileConfig);
            mdecorationNode->setParent(mSceneManager->getSceneNodeFromName("decorativeNodes"));
            video::Position3DCompatible position = tileConfig.position;
            video::Vector3DCompatible offset = tileConfig.offset;
            mdecorationNode->setPosition(position.toIrrlichtVector() + offset.toIrrlichtVector());
            defineAppearance(tileConfig.textureFileName.c_str());
        }

        Decoration::~Decoration() {
            video::MeshHelper::removeMeshFromVRAM(mdecorationNode->getMesh(), mSceneManager->getVideoDriver());
            mdecorationNode->remove();
        }

        void Decoration::setDesiredPostition(const video::Position3D& targetPosition) {
            mDesiredPosition = targetPosition;
        }

        void Decoration::transformSceneNode(const Node3DConfiguration& tileConfig) {
            video::Rotation3DCompatible rotation = tileConfig.rotation;
            video::Scale3DCompatible scale = tileConfig.scale;
            mdecorationNode->setRotation(rotation.toIrrlichtVector());
            mdecorationNode->setScale(scale.toIrrlichtVector());
        }

        void Decoration::defineAppearance(const char* textureFileName) {
            irr::video::ITexture* texture = mTextures.get(textureFileName);
            mdecorationNode->setMaterialTexture(0, texture);
            mdecorationNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            mdecorationNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
            mdecorationNode->setMaterialType(irr::video::EMT_SOLID);
            mdecorationNode->setVisible(true);
        }
    }
}
