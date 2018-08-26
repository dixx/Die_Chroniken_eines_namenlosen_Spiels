#include "Keyboard.h"

namespace leviathan
{
    namespace input
    {
        Keyboard::Keyboard()
        : keyIsDown_(),
          keyLastState_(),
          shiftIsDown_(false),
          shiftWasDown_(false),
          ctrlIsDown_(false),
          ctrlWasDown_(false)
        {
            keyIsDown_.fill(false);
            keyLastState_.fill(false);
        }

        bool Keyboard::isKeyDown(const irr::EKEY_CODE keycode) const
        {
            return keyIsDown_[ keycode ];
        }

        bool Keyboard::wasKeyDown(const irr::EKEY_CODE keycode) const
        {
            return keyLastState_[ keycode ];
        }

        bool Keyboard::hasKeyJustBeenSuppressed(const irr::EKEY_CODE keycode) const
        {
            return (isKeyDown(keycode) && !wasKeyDown(keycode));
        }

        bool Keyboard::hasKeyJustBeenReleased(const irr::EKEY_CODE keycode) const
        {
            return (!isKeyDown(keycode) && wasKeyDown(keycode));
        }

        bool Keyboard::isShiftDown() const
        {
            return shiftIsDown_;
        }

        bool Keyboard::wasShiftDown() const
        {
            return shiftWasDown_;
        }

        bool Keyboard::isCtrlDown() const
        {
            return ctrlIsDown_;
        }

        bool Keyboard::wasCtrlDown() const
        {
            return ctrlWasDown_;
        }

        void Keyboard::update()
        {
            keyLastState_ = keyIsDown_;
            shiftWasDown_ = shiftIsDown_;
            ctrlWasDown_ = ctrlIsDown_;
        }

        void Keyboard::setKeyState(const irr::EKEY_CODE keycode, const bool keyState, const bool shiftState,
            const bool ctrlState)
        {
            keyIsDown_[ keycode ] = keyState;
            shiftIsDown_ = shiftState;
            ctrlIsDown_ = ctrlState;
        }
    }
}
