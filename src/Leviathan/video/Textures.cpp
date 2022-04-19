#include "Textures.h"
#include "Constants.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include <core/ILogger.h>

namespace leviathan {
    namespace video {
        Textures::Textures(irr::video::IVideoDriver* videoDriver, leviathan::core::ILogger& logger)
        : mVideoDriver(videoDriver), mLogger(logger) {}

        irr::video::ITexture* Textures::get(const char* fileName) {
            if (mTextures.find(fileName) != mTextures.end()) return mTextures[fileName].irrTexture;

            mVideoDriver->setTextureCreationFlag(irr::video::ETCF_OPTIMIZED_FOR_QUALITY, true);
            mVideoDriver->setTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS, false);  // don't create LOD textures
            Texture tex;
            tex.irrTexture = mVideoDriver->getTexture(fileName);
            if (tex.irrTexture == nullptr) {
                mLogger.text << "[Warning] - cannot load texture " << fileName << "!";
                mLogger.write(mLogger.Level::DEBUG);
            }
            mTextures[fileName] = tex;
            return tex.irrTexture;
        }

        irr::video::ITexture* Textures::getWithColorKeyTransparency(const char* fileName) {
            irr::video::ITexture* texture = get(fileName);
            if (!mTextures[fileName].alreadyColorKeyed) {
                mVideoDriver->makeColorKeyTexture(texture, video::COL_MAGICPINK);
                mTextures[fileName].alreadyColorKeyed = true;
            }
            return texture;
        }
    }
}
