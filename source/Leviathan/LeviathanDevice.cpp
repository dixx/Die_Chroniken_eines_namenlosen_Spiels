#include "LeviathanDevice.h"

namespace leviathan
{
    LeviathanDevice::LeviathanDevice()
    : configuration_(),
      graphicEngine_( irr::createDeviceEx( configuration_.getGraphicEngineParams() ) ),
      timeControl_(),
      logger_(
          new leviathan::core::Logger(
              graphicEngine_->getFileSystem(),
              graphicEngine_->getTimer(),
    #ifdef _DEBUG_MODE
              "debug.log",
    #else
              "game.log",
    #endif
              leviathan::core::Logger::INFO // TODO get from config
          )
      )
    {
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

    void LeviathanDevice::init( const irr::io::path& fileName )
    {
        configuration_.readFromFile( fileName, graphicEngine_->getFileSystem() );
        delete logger_;
        graphicEngine_->closeDevice();
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
            leviathan::core::Logger::INFO, // TODO get from config
            /*append = */ true
        );
    }

    core::Logger& LeviathanDevice::Logger()
    {
        return *logger_;
    }

    core::TimeControl& LeviathanDevice::TimeControl()
    {
        return timeControl_;
    }

    core::Configuration& LeviathanDevice::Configuration()
    {
        return configuration_;
    }
}
