#include "Mouse.h"

namespace leviathan
{
    namespace input
    {
        Mouse::Mouse()
        : buttonIsDown_(),
          buttonLastState_(),
          position_(0, 0),
          lastPosition_(0, 0),
          wheelData_(0.0f)
        {
            buttonIsDown_.fill( false );
            buttonLastState_.fill( false );
        }

        void Mouse::update()
        {
            buttonLastState_ = buttonIsDown_;
            lastPosition_ = position_;
        }

        bool Mouse::isLMBDown() const
        {
            return buttonIsDown_[ LEFT ];
        }

        bool Mouse::isMMBDown() const
        {
            return buttonIsDown_[ MIDDLE ];
        }

        bool Mouse::isRMBDown() const
        {
            return buttonIsDown_[ RIGHT ];
        }

        bool Mouse::wasLMBDown() const
        {
            return buttonLastState_[ LEFT ];
        }

        bool Mouse::wasMMBDown() const
        {
            return buttonLastState_[ MIDDLE ];
        }

        bool Mouse::wasRMBDown() const
        {
            return buttonLastState_[ RIGHT ];
        }

        const irr::core::position2di& Mouse::getPosition() const
        {
            return position_;
        }

        const irr::core::position2di& Mouse::getLastPosition() const
        {
            return lastPosition_;
        }

        float Mouse::getWheelDelta() const
        {
            return wheelData_;
        }

        void Mouse::setMouseButtonState( const Button button, const bool state )
        {
            buttonIsDown_[ button ] = state;
        }

        void Mouse::setMouseCoordinateState( const int32_t x, const int32_t y )
        {
            position_.X = x;
            position_.Y = y;
        }

        void Mouse::setMouseWheelState( const float delta )
        {
            wheelData_ = delta;
        }
    }
}
