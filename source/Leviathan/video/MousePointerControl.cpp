#include "MousePointerControl.h"

namespace leviathan {
    namespace video {
        MousePointerControl::MousePointerControl(
            leviathan::input::IEventProducer& producer, irr::IrrlichtDevice* graphicDevice)
        : graphicDevice_(graphicDevice) {
            producer.subscribe(*this, irr::EET_MOUSE_INPUT_EVENT);
        }

        bool MousePointerControl::onEvent(const irr::SEvent& event) {
            if (event.MouseInput.Event != irr::EMIE_MOUSE_MOVED)
                return false;
            position_.X = event.MouseInput.X;
            position_.Y = event.MouseInput.Y;
            return true;
        }

        void MousePointerControl::createMousePointer(const uint32_t id, const irr::io::path& imageFileName,
            const irr::core::recti& imageArea, const irr::core::vector2di& hotSpot) {
            (void)id;
            (void)imageFileName;
            (void)imageArea;
            (void)hotSpot;
        }

        void MousePointerControl::setActiveMousPointer(const uint32_t id) {
            (void)id;
        }

        void MousePointerControl::draw() {
            graphicDevice_->getVideoDriver()->draw2DImage(
                    baseImage_.at(activeMousePointer_),
                    position_ - hotSpot_.at(activeMousePointer_), // upper left corner of mouse pointer image
                    imageArea_.at(activeMousePointer_),
                    nullptr, // clipping rectangle, not used here
                    backgroundColor_, // white for fully opaque mouse pointer image
                    true // use alpha channel for transparent parts of the mouse pointer image
            );
        }
    }
}
