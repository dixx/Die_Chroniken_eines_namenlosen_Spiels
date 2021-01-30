#include "Textures.h"

namespace leviathan {
    namespace video {
        Textures::Textures(irr::video::IVideoDriver* videoDriver, leviathan::core::Logger& logger)
        : videoDriver_(videoDriver), logger_(logger) {}

        irr::video::ITexture* Textures::get(const char* fileName) {
            videoDriver_->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);  // don't create LOD textures
            irr::video::ITexture* texture = videoDriver_->getTexture(fileName);
            if (texture == nullptr) {
                logger_.text << "[Warning] - cannot load texture " << fileName << "!";
                logger_.write(core::Logger::Level::DEBUG);
                return nullptr;
            }
            return texture;
        }
    }
}
