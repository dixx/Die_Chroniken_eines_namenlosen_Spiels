#include "Textures.h"
#include "../core/Logger.h"
#include "Constants.h"
#include "ITexture.h"
#include "IVideoDriver.h"

namespace leviathan {
    namespace video {
        Textures::Textures(irr::video::IVideoDriver* videoDriver, leviathan::core::Logger& logger)
        : videoDriver_(videoDriver), logger_(logger) {}

        irr::video::ITexture* Textures::get(const char* fileName) {
            if (textures_.find(fileName) != textures_.end()) return textures_[fileName].irrTexture;

            videoDriver_->setTextureCreationFlag(irr::video::ETCF_OPTIMIZED_FOR_QUALITY, true);
            videoDriver_->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);  // don't create LOD textures
            Texture tex;
            tex.irrTexture = videoDriver_->getTexture(fileName);
            if (tex.irrTexture == nullptr) {
                logger_.text << "[Warning] - cannot load texture " << fileName << "!";
                logger_.write(core::Logger::Level::DEBUG);
            }
            textures_[fileName] = tex;
            return tex.irrTexture;
        }

        irr::video::ITexture* Textures::getWithColorKeyTransparency(const char* fileName) {
            irr::video::ITexture* texture = get(fileName);
            if (!textures_[fileName].alreadyColorKeyed) {
                videoDriver_->makeColorKeyTexture(texture, video::COL_MAGICPINK);
                textures_[fileName].alreadyColorKeyed = true;
            }
            return texture;
        }
    }
}
