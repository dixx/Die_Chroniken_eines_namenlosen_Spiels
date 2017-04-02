#include "LeviathanDevice.h"

namespace leviathan
{
    LeviathanDevice::LeviathanDevice()
    : configuration_(),
      graphicEngine_( irr::createDeviceEx( configuration_.getGraphicEngineParams() ) ),
      timeControl_(),
      logger_( 0 )
    {
        configuration_.readFromFile( "config.ini", graphicEngine_->getFileSystem() );
        graphicEngine_->drop();
        graphicEngine_ = irr::createDeviceEx( configuration_.getGraphicEngineParams() );
        logger_ = new leviathan::core::Logger(
            graphicEngine_->getFileSystem(),
            graphicEngine_->getTimer(),
#ifdef _DEBUG_MODE
            "debug.log",
#else
            "game.log",
#endif
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

    core::Configuration& LeviathanDevice::getConfiguration()
    {
        return configuration_;
    }
}
