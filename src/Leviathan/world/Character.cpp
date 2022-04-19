#include "Character.h"
#include "../video/Textures.h"
#include "../video/Vector3DCompatible.h"
#include <EMaterialFlags.h>
#include <IAnimatedMesh.h>
#include <IAnimatedMeshSceneNode.h>
#include <ISceneManager.h>
#include <characters/CharacterConfiguration.h>

namespace leviathan {
    namespace world {
        Character::Character(const characters::CharacterConfiguration& characterConfig, video::Textures& textures,
            irr::scene::ISceneManager* sceneManager) {
            mOffset = characterConfig.playableFigurineConfiguration.offset;
            createNode(characterConfig, sceneManager);
            mCharacterNode->setName(characterConfig.internalName.c_str());
            setScale(characterConfig.playableFigurineConfiguration.scale);
            setPosition(characterConfig.playableFigurineConfiguration.position);
            irr::video::ITexture* texture = textures.get(
                characterConfig.playableFigurineConfiguration.textureFileName.c_str());
            mCharacterNode->setMaterialTexture(0, texture);
            mCharacterNode->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            mCharacterNode->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, false);
            mCharacterNode->setMaterialType(irr::video::EMT_SOLID);
            mCharacterNode->setMD2Animation(irr::scene::EMAT_STAND);
            setInvisible();
        }

        Character::~Character() {
            mCharacterNode->remove();
        }

        void Character::setDesiredPostition(const video::Position3D& targetPosition) {
            mDesiredPosition = targetPosition;
        }

        void Character::setPosition(const video::Position3D& position) {
            mCharacterNode->setPosition(video::Vector3DCompatible(position).toIrrlichtVector()
                                        + video::Vector3DCompatible(mOffset).toIrrlichtVector());
            mCharacterNode->updateAbsolutePosition();
        }

        void Character::setVisible() {
            mCharacterNode->setVisible(true);
        }

        void Character::setInvisible() {
            mCharacterNode->setVisible(false);
        }

        std::string Character::getName() const {
            return mCharacterNode->getName();
        }

        video::Position3D Character::getPosition() const {
            auto position = mCharacterNode->getAbsolutePosition();
            return {position.X, position.Y, position.Z};
        }

        video::Rotation3D Character::getRotation() const {
            auto rotation = mCharacterNode->getRotation();
            return {rotation.X, rotation.Y, rotation.Z};
        }

        void Character::setRotation(const video::Rotation3D& rotation) {
            mCharacterNode->setRotation(video::Vector3DCompatible(rotation).toIrrlichtVector());
        }

        /* private */

        void Character::createNode(
            const characters::CharacterConfiguration& config, irr::scene::ISceneManager* sceneManager) {
            irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh(
                config.playableFigurineConfiguration.meshFileName.c_str());
            mCharacterNode = sceneManager->addAnimatedMeshSceneNode(mesh);
        }

        void Character::setScale(const video::Scale3D& scale) {
            mCharacterNode->setScale(video::Vector3DCompatible(scale).toIrrlichtVector());
        }
    }
}
