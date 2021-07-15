#include "Character.h"
#include "../video/Vector3DCompatible.h"
#include <EMaterialFlags.h>
#include <IAnimatedMesh.h>
#include <IAnimatedMeshSceneNode.h>
#include <ISceneManager.h>
#include <characters/CharacterConfiguration.h>

namespace leviathan {
    namespace world {
        Character::Character(
            const characters::CharacterConfiguration& characterConfig, irr::scene::ISceneManager* sceneManager) {
            offset_ = characterConfig.playableFigurineConfiguration.offset;
            createNode(characterConfig, sceneManager);
            characterNode_->setName(characterConfig.internalName.c_str());
            setScale(characterConfig.playableFigurineConfiguration.scale);
            setPosition(characterConfig.playableFigurineConfiguration.position);
            // TODO: replace with video::Textures.get
            irr::video::ITexture* texture = sceneManager->getVideoDriver()->getTexture(
                characterConfig.playableFigurineConfiguration.textureFileName.c_str());
            characterNode_->setMaterialTexture(0, texture);
            characterNode_->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            characterNode_->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
            characterNode_->setMD2Animation(irr::scene::EMAT_STAND);
            setInvisible();
        }

        Character::~Character() {
            characterNode_->remove();
        }

        void Character::setDesiredPostition(const video::Position3D& targetPosition) {
            desiredPosition_ = targetPosition;
        }

        void Character::setPosition(const video::Position3D& position) {
            characterNode_->setPosition(video::Vector3DCompatible(position).toIrrlichtVector()
                                        + video::Vector3DCompatible(offset_).toIrrlichtVector());
            characterNode_->updateAbsolutePosition();
        }

        void Character::setVisible() {
            characterNode_->setVisible(true);
        }

        void Character::setInvisible() {
            characterNode_->setVisible(false);
        }

        std::string Character::getName() const {
            return characterNode_->getName();
        }

        video::Position3D Character::getPosition() const {
            auto position = characterNode_->getAbsolutePosition();
            return {position.X, position.Y, position.Z};
        }

        video::Rotation3D Character::getRotation() const {
            auto rotation = characterNode_->getRotation();
            return {rotation.X, rotation.Y, rotation.Z};
        }

        void Character::setRotation(const video::Rotation3D& rotation) {
            characterNode_->setRotation(video::Vector3DCompatible(rotation).toIrrlichtVector());
        }

        /* private */

        void Character::createNode(
            const characters::CharacterConfiguration& config, irr::scene::ISceneManager* sceneManager) {
            irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh(
                config.playableFigurineConfiguration.meshFileName.c_str());
            characterNode_ = sceneManager->addAnimatedMeshSceneNode(mesh);
        }

        void Character::setScale(const video::Scale3D& scale) {
            characterNode_->setScale(video::Vector3DCompatible(scale).toIrrlichtVector());
        }
    }
}
