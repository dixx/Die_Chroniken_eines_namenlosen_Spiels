#include "LeviathanDevice.h"

namespace leviathan
{
    LeviathanDevice::LeviathanDevice()
    : graphicEngine_(0),
      timeControl_()
    {
        graphicEngine_ = irr::createDevice( irr::video::EDT_NULL );
    }


    LeviathanDevice::~LeviathanDevice()
    {
        if ( graphicEngine_ )
        {
            graphicEngine_->drop();
            graphicEngine_ = 0;
        }
    }
}
