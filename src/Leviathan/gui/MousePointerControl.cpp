#include "MousePointerControl.h"
#include "../input/IEventProducer.h"
#include "../video/Textures.h"
#include "ICursorControl.h"
#include "ITexture.h"
#include "IVideoDriver.h"
#include <core/ILogger.h>
#include <gui/MousePointerConfiguration.h>
#include <stdexcept>

namespace leviathan {
    namespace gui {
        MousePointerControl::MousePointerControl(leviathan::input::IEventProducer& producer,
            video::GraphicEngine& graphicDevice, leviathan::core::ILogger& logger, leviathan::video::Textures& textures)
        : mLogger(logger), mTextures(textures), mGraphicDevice(graphicDevice) {
            producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
        }

        bool MousePointerControl::onEvent(const irr::SEvent& event) {
            if (event.MouseInput.Event != irr::EMIE_MOUSE_MOVED) return false;

            mPosition.X = event.MouseInput.X;
            mPosition.Y = event.MouseInput.Y;
            return true;
        }

        void MousePointerControl::addMousePointer(const uint32_t id, const MousePointerConfiguration& configuration) {
            if (mBaseImage[id] != nullptr) {
                mLogger.text << "[Warning] - MousePointerControl - id " << id << " already exists!";
                mLogger.write(mLogger.Level::DEBUG);
                return;
            }

            irr::video::ITexture* texture = mTextures.getWithColorKeyTransparency(configuration.imageFileName.c_str());
            if (texture == nullptr) return;

            mBaseImage[id] = texture;
            mImageArea[id] = irr::core::recti(configuration.imageArea.upperLeft.x, configuration.imageArea.upperLeft.y,
                configuration.imageArea.lowerRight.x, configuration.imageArea.lowerRight.y);
            mHotSpot[id] = irr::core::vector2di(configuration.hotSpot.x, configuration.hotSpot.y);
        }

        void MousePointerControl::setActiveMousPointer(const uint32_t id) {
            mActiveMousePointer = id;
            try {
                mHotSpot.at(mActiveMousePointer);
                mGraphicDevice.getCursorControl()->setVisible(false);
            } catch (const std::out_of_range& _) {
                mLogger.text << "[Warning] - MousePointerControl - id " << id << " does not exist!";
                mLogger.write(mLogger.Level::DEBUG);
                mActiveMousePointer = 0;
                mGraphicDevice.getCursorControl()->setVisible(true);
            }
        }

        const video::Position2D MousePointerControl::getPosition() const {
            return {mPosition.X, mPosition.Y};
        }

        void MousePointerControl::draw() {
            if (mActiveMousePointer == 0) return;

            mGraphicDevice.getVideoDriver()->draw2DImage(mBaseImage.at(mActiveMousePointer),
                mPosition - mHotSpot.at(mActiveMousePointer),  // upper left corner of mouse pointer image
                mImageArea.at(mActiveMousePointer),
                nullptr,  // clipping rectangle, not used here
                mBackgroundColor,  // white for fully opaque mouse pointer image
                true  // use alpha channel for transparent parts of the mouse pointer image
            );
        }
    }
}
