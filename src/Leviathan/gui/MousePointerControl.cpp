#include "MousePointerControl.h"
#include <stdexcept>

namespace leviathan {
    namespace gui {
        MousePointerControl::MousePointerControl(leviathan::input::IEventProducer& producer,
            video::GraphicEngine& graphicDevice, leviathan::core::Logger& logger, leviathan::video::Textures& textures)
        : logger_(logger), textures_(textures), graphicDevice_(graphicDevice) {
            producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
        }

        bool MousePointerControl::onEvent(const irr::SEvent& event) {
            if (event.MouseInput.Event != irr::EMIE_MOUSE_MOVED) return false;

            position_.X = event.MouseInput.X;
            position_.Y = event.MouseInput.Y;
            return true;
        }

        void MousePointerControl::addMousePointer(const uint32_t id, const irr::io::path& imageFileName,
            const irr::core::recti& imageArea, const irr::core::vector2di& hotSpot) {
            if (baseImage_[id] != nullptr) {
                logger_.text << "[Warning] - MousePointerControl - id " << id << " already exists!";
                logger_.write(leviathan::core::Logger::Level::DEBUG);
                return;
            }

            irr::video::ITexture* texture = textures_.getWithColorKeyTransparency(imageFileName.c_str());
            if (texture == nullptr) return;

            baseImage_[id] = texture;
            imageArea_[id] = imageArea;
            hotSpot_[id] = hotSpot;
        }

        void MousePointerControl::setActiveMousPointer(const uint32_t id) {
            activeMousePointer_ = id;
            try {
                hotSpot_.at(activeMousePointer_);
                graphicDevice_.getCursorControl()->setVisible(false);
            } catch (const std::out_of_range& _) {
                logger_.text << "[Warning] - MousePointerControl - id " << id << " does not exist!";
                logger_.write(leviathan::core::Logger::Level::DEBUG);
                activeMousePointer_ = 0;
                graphicDevice_.getCursorControl()->setVisible(true);
            }
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
