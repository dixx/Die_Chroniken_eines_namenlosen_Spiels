#include "irrlicht.h"

// Fakeit cannot mock classes with multiple inheritance, so we must implement our own mocks :(
namespace mocks {
    class IGUIImageMock : public irr::gui::IGUIImage {
    public:
        IGUIImageMock(irr::gui::IGUIEnvironment* environment, irr::gui::IGUIElement* parent, irr::s32 id, irr::core::rect<irr::s32> rectangle)
            : IGUIImage(environment, parent, id, rectangle) {}
        void setImage(irr::video::ITexture* image) { (void)image; }
        irr::video::ITexture* getImage() const { return nullptr; }
        void setColor(irr::video::SColor color) { (void)color; }
        void setScaleImage(bool scale) { (void)scale; }
        void setUseAlphaChannel(bool use) { (void)use; }
        irr::video::SColor getColor() const { return mDummySColor; }
        bool isImageScaled() const { return false; }
        bool isAlphaChannelUsed() const { return false; }
    private:
        irr::video::SColor mDummySColor = irr::video::SColor();
    };
}
