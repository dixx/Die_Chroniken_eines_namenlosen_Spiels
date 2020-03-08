#include "MousePointerControl.h"
#include "Constants.h"
#include <stdexcept>

namespace leviathan {
    namespace video {
        MousePointerControl::MousePointerControl(leviathan::input::IEventProducer& producer,
            irr::IrrlichtDevice* graphicDevice, leviathan::core::Logger& logger)
        : logger_(logger), graphicDevice_(graphicDevice) {
            producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
        }

        bool MousePointerControl::onEvent(const irr::SEvent& event) {
            if (event.MouseInput.Event != irr::EMIE_MOUSE_MOVED) return false;
            position_.X = event.MouseInput.X;
            position_.Y = event.MouseInput.Y;
            return true;
        }

        void MousePointerControl::createMousePointer(const uint32_t id, const irr::io::path& imageFileName,
            const irr::core::recti& imageArea, const irr::core::vector2di& hotSpot) {
            irr::video::ITexture* texture = graphicDevice_->getVideoDriver()->getTexture(imageFileName);
            if (texture == nullptr) {
                logger_.text << "[Warning] - MousePointerControl - cannot load texture " << imageFileName.c_str()
                             << "!";
                logger_.write(leviathan::core::Logger::Level::DEBUG);
                return;
            }
            if (baseImage_[id] != nullptr) {
                logger_.text << "[Warning] - MousePointerControl - id " << id << " already exists!";
                logger_.write(leviathan::core::Logger::Level::DEBUG);
                return;
            }
            baseImage_[id] = texture;
            graphicDevice_->getVideoDriver()->makeColorKeyTexture(baseImage_[id], COL_MAGICPINK);
            imageArea_[id] = imageArea;
            hotSpot_[id] = hotSpot;
        }

        void MousePointerControl::setActiveMousPointer(const uint32_t id) {
            activeMousePointer_ = id;
            try {
                hotSpot_.at(activeMousePointer_);
                graphicDevice_->getCursorControl()->setVisible(false);
            } catch (const std::out_of_range& _) {
                logger_.text << "[Warning] - MousePointerControl - id " << id << " does not exist!";
                logger_.write(leviathan::core::Logger::Level::DEBUG);
                activeMousePointer_ = 0;
                graphicDevice_->getCursorControl()->setVisible(true);
            }
        }

        void MousePointerControl::draw() {
            if (activeMousePointer_ == 0) return;
            graphicDevice_->getVideoDriver()->draw2DImage(baseImage_.at(activeMousePointer_),
                position_ - hotSpot_.at(activeMousePointer_),  // upper left corner of mouse pointer image
                imageArea_.at(activeMousePointer_),
                nullptr,  // clipping rectangle, not used here
                backgroundColor_,  // white for fully opaque mouse pointer image
                true  // use alpha channel for transparent parts of the mouse pointer image
            );
        }
    }
}
