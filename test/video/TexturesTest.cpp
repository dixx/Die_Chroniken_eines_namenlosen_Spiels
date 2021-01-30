#include "../../source/Leviathan/video/Textures.h"
#include "../helpers/TestHelper.h"
#include "IImage.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)

TEST_CASE("Textures", "[integration]") {
    irr::video::IVideoDriver* videoDriver = TestHelper::graphicEngine()->getVideoDriver();
    const char* textureFileName = "sampleTexture.jpg";
    irr::video::IImage* sampleImage = videoDriver->createImage(irr::video::ECF_A1R5G5B5, {1, 1});
    leviathan::video::Textures subject(videoDriver, TestHelper::Logger());

    SECTION("can be retrieved by file name") {
        videoDriver->writeImageToFile(sampleImage, textureFileName);  // create a test image file
        irr::video::ITexture* sampleTexture = subject.get(textureFileName);
        REQUIRE(sampleTexture != nullptr);

        SECTION("with only basic features") {
            REQUIRE_FALSE(videoDriver->getTextureCreationFlag(irr::video::ETCF_CREATE_MIP_MAPS));
        }

        SECTION("are loaded only once") {
            TestHelper::deleteFile(textureFileName);  // delete the image file, now only the image in memory remains
            REQUIRE(subject.get(textureFileName) == sampleTexture);
        }
    }

    SECTION("can have color-keyed transparency") {
        SECTION("which will be done only once") {}
    }

    SECTION("can be removed from memory") {}
}
