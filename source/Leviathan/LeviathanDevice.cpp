#include "LeviathanDevice.h"

namespace leviathan
{
    LeviathanDevice::LeviathanDevice()
    : graphicEngine_( 0 ),
      timeControl_(),
      logger_( 0 )
    {
        graphicEngine_ = irr::createDevice( irr::video::EDT_NULL );
        // get config
        logger_ = new leviathan::core::Logger(
            graphicEngine_->getFileSystem(),
            graphicEngine_->getTimer(),
            "game.log",
            leviathan::core::Logger::INFO // TODO get from config
        );
    }


    LeviathanDevice::~LeviathanDevice()
    {
        if ( logger_ )
        {
            delete logger_;
            logger_ = 0;
        }
        if ( graphicEngine_ )
        {
            graphicEngine_->drop();
            graphicEngine_ = 0;
        }
    }

    core::Logger& LeviathanDevice::getLogger()
    {
        return *logger_;
    }

    core::TimeControl& LeviathanDevice::getTimeControl()
    {
        return timeControl_;
    }

}
