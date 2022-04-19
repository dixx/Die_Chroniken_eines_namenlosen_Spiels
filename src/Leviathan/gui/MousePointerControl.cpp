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
        : logger_(logger), textures_(textures), graphicDevice_(graphicDevice) {
            producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
        }

        bool MousePointerControl::onEvent(const irr::SEvent& event) {
            if (event.MouseInput.Event != irr::EMIE_MOUSE_MOVED) return false;

            position_.X = event.MouseInput.X;
            position_.Y = event.MouseInput.Y;
            return true;
        }

        void MousePointerControl::addMousePointer(const uint32_t id, const MousePointerConfiguration& configuration) {
            if (baseImage_[id] != nullptr) {
                logger_.text << "[Warning] - MousePointerControl - id " << id << " already exists!";
                logger_.write(logger_.Level::DEBUG);
                return;
            }

            irr::video::ITexture* texture = textures_.getWithColorKeyTransparency(configuration.imageFileName.c_str());
            if (texture == nullptr) return;

            baseImage_[id] = texture;
            imageArea_[id] = irr::core::recti(configuration.imageArea.upperLeft.x, configuration.imageArea.upperLeft.y,
                configuration.imageArea.lowerRight.x, configuration.imageArea.lowerRight.y);
            hotSpot_[id] = irr::core::vector2di(configuration.hotSpot.x, configuration.hotSpot.y);
        }

        void MousePointerControl::setActiveMousPointer(const uint32_t id) {
            activeMousePointer_ = id;
            try {
                hotSpot_.at(activeMousePointer_);
                graphicDevice_.getCursorControl()->setVisible(false);
            } catch (const std::out_of_range& _) {
                logger_.text << "[Warning] - MousePointerControl - id " << id << " does not exist!";
                logger_.write(logger_.Level::DEBUG);
                activeMousePointer_ = 0;
                graphicDevice_.getCursorControl()->setVisible(true);
            }
        }

        const video::Position2D MousePointerControl::getPosition() const {
            return {position_.X, position_.Y};
        }

        void MousePointerControl::draw() {
            if (activeMousePointer_ == 0) return;

            graphicDevice_.getVideoDriver()->draw2DImage(baseImage_.at(activeMousePointer_),
                position_ - hotSpot_.at(activeMousePointer_),  // upper left corner of mouse pointer image
                imageArea_.at(activeMousePointer_),
                nullptr,  // clipping rectangle, not used here
                backgroundColor_,  // white for fully opaque mouse pointer image
                true  // use alpha channel for transparent parts of the mouse pointer image
            );
        }
    }
}
