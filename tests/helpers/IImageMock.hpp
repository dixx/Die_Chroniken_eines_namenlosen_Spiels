#include "IImage.h"
#include "SColor.h"
#include "dimension2d.h"
#include "position2d.h"
#include "rect.h"

// Fakeit cannot mock classes with multiple inheritance, so we must implement our own mocks :(
namespace mocks {
    class IImageMock : public irr::video::IImage {
    public:
        void* lock() {
            return nullptr;
        }
        void unlock() {}
        const irr::core::dimension2d<irr::u32>& getDimension() const {
            return mDummyDimension2du;
        }
        irr::u32 getBitsPerPixel() const {
            return 0;
        }
        irr::u32 getBytesPerPixel() const {
            return 0;
        }
        irr::u32 getImageDataSizeInBytes() const {
            return 0;
        }
        irr::u32 getImageDataSizeInPixels() const {
            return 0;
        }
        irr::video::SColor getPixel(irr::u32 x, irr::u32 y) const {
            (void)x;
            (void)y;
            return mDummySColor;
        }
        void setPixel(irr::u32 x, irr::u32 y, const irr::video::SColor& color, bool blend = false) {
            (void)x;
            (void)y;
            (void)color;
            (void)blend;
        }
        irr::video::ECOLOR_FORMAT getColorFormat() const {
            return irr::video::ECF_A8R8G8B8;
        }
        irr::u32 getRedMask() const {
            return 0;
        }
        irr::u32 getGreenMask() const {
            return 0;
        }
        irr::u32 getBlueMask() const {
            return 0;
        }
        irr::u32 getAlphaMask() const {
            return 0;
        }
        irr::u32 getPitch() const {
            return 0;
        }
        void copyToScaling(void* target, irr::u32 width, irr::u32 height,
            irr::video::ECOLOR_FORMAT format = irr::video::ECF_A8R8G8B8, irr::u32 pitch = 0) {
            (void)target;
            (void)width;
            (void)height;
            (void)format;
            (void)pitch;
        }
        void copyToScaling(irr::video::IImage* target) {
            (void)target;
        }
        void copyTo(irr::video::IImage* target,
            const irr::core::position2d<irr::s32>& pos = irr::core::position2d<irr::s32>(0, 0)) {
            (void)target;
            (void)pos;
        }
        void copyTo(irr::video::IImage* target, const irr::core::position2d<irr::s32>& pos,
            const irr::core::rect<irr::s32>& sourceRect, const irr::core::rect<irr::s32>* clipRect = 0) {
            (void)target;
            (void)pos;
            (void)sourceRect;
            (void)clipRect;
        }
        void copyToWithAlpha(irr::video::IImage* target, const irr::core::position2d<irr::s32>& pos,
            const irr::core::rect<irr::s32>& sourceRect, const irr::video::SColor& color,
            const irr::core::rect<irr::s32>* clipRect = 0) {
            (void)target;
            (void)pos;
            (void)sourceRect;
            (void)color;
            (void)clipRect;
        }
        void copyToScalingBoxFilter(irr::video::IImage* target, irr::s32 bias = 0, bool blend = false) {
            (void)target;
            (void)bias;
            (void)blend;
        }
        void fill(const irr::video::SColor& color) {
            (void)color;
        }

    private:
        irr::core::dimension2d<irr::u32> mDummyDimension2du = irr::core::dimension2d<irr::u32>();
        irr::video::SColor mDummySColor = irr::video::SColor();
    };
}
