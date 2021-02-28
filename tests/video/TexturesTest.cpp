#include "../../source/Leviathan/video/Textures.h"
#include "../../source/Leviathan/video/Constants.h"
#include "../helpers/TestHelper.h"
#include "IImage.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include "catch.hpp"
#include "fakeit.hpp"

using namespace fakeit;

#define getTextureArgs irr::video::ITexture*(const irr::io::path&)
#define makeColorKeyTextureArgs void(irr::video::ITexture*, irr::video::SColor, bool)

TEST_CASE("Textures", "[integration]") {
    irr::video::IVideoDriver* videoDriver = TestHelper::graphicEngine()->getVideoDriver();
    Mock<irr::video::IVideoDriver> videoDriverSpy(*(TestHelper::graphicEngine()->getVideoDriver()));
    Mock<irr::video::ITexture> textureMock;
    When(OverloadedMethod(videoDriverSpy, getTexture, getTextureArgs)).AlwaysReturn(&textureMock.get());
    Fake(ConstOverloadedMethod(videoDriverSpy, makeColorKeyTexture, makeColorKeyTextureArgs));
    const char* textureFileName = "sampleTexture.jpg";
    irr::video::IImage* sampleImage = videoDriver->createImage(irr::video::ECF_A1R5G5B5, {1, 1});
    videoDriver->writeImageToFile(sampleImage, textureFileName);  // create a test image file

    leviathan::video::Textures subject(videoDriver, TestHelper::Logger());

    SECTION("can be retrieved by file name") {
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
        irr::video::ITexture* sampleTexture = subject.getWithColorKeyTransparency(textureFileName);
        REQUIRE(sampleTexture != nullptr);
        Verify(ConstOverloadedMethod(videoDriverSpy, makeColorKeyTexture, makeColorKeyTextureArgs)
                   .Using(sampleTexture, leviathan::video::COL_MAGICPINK, false))
            .Once();

        SECTION("which will be done only once") {
            irr::video::ITexture* sameSampleTexture = subject.getWithColorKeyTransparency(textureFileName);
            REQUIRE(sameSampleTexture == sampleTexture);
            VerifyNoOtherInvocations(
                ConstOverloadedMethod(videoDriverSpy, makeColorKeyTexture, makeColorKeyTextureArgs));
        }
    }

    SECTION("can be removed from memory") {}
}
