#include "LeviathanDevice.h"
#include <cstdint>

namespace leviathan
{
    LeviathanDevice::LeviathanDevice()
    : configuration_(),
      graphicEngine_( irr::createDeviceEx( configuration_.getGraphicEngineParams() ) ),
      timeControl_(),
      gameStateManager_(),
      logger_(
          new leviathan::core::Logger(
              graphicEngine_->getFileSystem(),
              graphicEngine_->getTimer(),
              LOG_FILE_NAME,
              configuration_.getLoggingLevel()
          )
      )
    {
    }

    LeviathanDevice::~LeviathanDevice()
    {
        if ( logger_ )
            delete logger_;
        if ( graphicEngine_ )
            graphicEngine_->drop();
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
            LOG_FILE_NAME,
            configuration_.getLoggingLevel(),
            /*append = */ true
        );
    }

    void LeviathanDevice::run()
    {
        const float FRAME_DELTA_TIME = 1.f / static_cast<float>( configuration_.getMaxFPS() );
        const uint32_t FRAME_DELTA_TIME_IN_MILLISECONDS = 1000 / configuration_.getMaxFPS();  // for performance.
        uint32_t next = graphicEngine_->getTimer()->getTime();

        while ( graphicEngine_->run() )
        {
            if ( !graphicEngine_->isWindowActive() )
                graphicEngine_->yield();
            uint32_t loops = 0;
            bool we_must_draw = false;
            while ( graphicEngine_->getTimer()->getTime() > next && loops < 10 ) // in-game time will slow down if framerate drops below 10% of maxFPS // FIXME for FPS > 250
            {
                timeControl_.tick( FRAME_DELTA_TIME );
                gameStateManager_.update( FRAME_DELTA_TIME );
                if ( !graphicEngine_->run() )
                {
                    we_must_draw = false;
                    break;
                }
                // eventreceiver.setKeysLastState();
                next += FRAME_DELTA_TIME_IN_MILLISECONDS;
                we_must_draw = true;
                // if ( gameStateManager_.allFramesMustBeShown() )
                //     break;
                ++loops;
            }
            if ( we_must_draw )
                gameStateManager_.draw();
        }
    }

    int LeviathanDevice::exitStatus()
    {
        return 0;
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

    core::GameStateManager& LeviathanDevice::GameStateManager()
    {
        return gameStateManager_;
    }
}
