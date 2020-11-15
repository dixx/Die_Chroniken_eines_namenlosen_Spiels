#include "Hero.h"

namespace leviathan {
    namespace characters {
        Hero::Hero(const std::string& internalName, irr::scene::ISceneManager* sceneManager) {
            irr::scene::IAnimatedMesh* mesh = sceneManager->getMesh("gfx/sydney.md2");
            // smgr_->getVideoDriver()->setTransform( irr::video::ETS_WORLD, irr::core::matrix4() );
            node_ = sceneManager->addAnimatedMeshSceneNode(mesh);
            node_->setName(internalName.c_str());
            irr::video::ITexture* texture = sceneManager->getVideoDriver()->getTexture("gfx/sydney.bmp");
            node_->setMaterialTexture(0, texture);
        }

        void Hero::update() {}

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
