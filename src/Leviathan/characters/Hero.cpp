#include "Hero.h"

namespace leviathan {
    namespace characters {
        Hero::Hero(const std::string& internalName, irr::scene::ISceneManager* sceneManager) {
            irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh("gfx/sydney.md2");
            node_ = sceneManager->addAnimatedMeshSceneNode(mesh);
            node_->setName(internalName.c_str());
            node_->setScale(irr::core::vector3df(0.025f, 0.025f, 0.025f));
            irr::video::ITexture* texture = sceneManager->getVideoDriver()->getTexture("gfx/sydney.bmp");
            node_->setMaterialTexture(0, texture);
            node_->setMaterialFlag(irr::video::EMF_LIGHTING, false);
            node_->setMaterialFlag(irr::video::EMF_NORMALIZE_NORMALS, true);
            node_->setMD2Animation(irr::scene::EMAT_STAND);
            disablePlayableCharacter();
        }

        void Hero::enablePlayableCharacter() {
            node_->setVisible(true);
        }

        void Hero::disablePlayableCharacter() {
            node_->setVisible(false);
        }

        const std::string Hero::getInternalName() const {
            return node_->getName();
        }

        irr::core::vector3df Hero::getPosition() const {
            return node_->getPosition();
        }

        void Hero::setPosition(const irr::core::vector3df& position) {
            node_->setPosition(position);
        }

        irr::core::vector3df Hero::getRotation() const {
            return node_->getRotation();
        }

        void Hero::setRotation(const irr::core::vector3df& rotation) {
            node_->setRotation(rotation);
        }
    }
}
