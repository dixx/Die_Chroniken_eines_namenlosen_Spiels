#include "LeviathanDevice.h"

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
#ifdef _DEBUG_MODE
              "debug.log",
#else
              "game.log",
#endif
              configuration_.getLoggingLevel()
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
            configuration_.getLoggingLevel(),
            /*append = */ true
        );
    }

    void LeviathanDevice::run()
    {
        const irr::f32 FRAME_DELTA_TIME = 0.008f;  // 0.008s ~= 125 FPS fixed
        const irr::u32 FRAME_DELTA_TIME_IN_MS = static_cast<irr::u32>( FRAME_DELTA_TIME * 1000 );  // for performance.
        irr::u32 next = graphicEngine_->getTimer()->getTime();

        while ( graphicEngine_->run() )
        {
            if ( !graphicEngine_->isWindowActive() )
                graphicEngine_->yield();
            irr::u32 loops = 0;
            bool we_must_draw = false;
            while ( graphicEngine_->getTimer()->getTime() > next && loops < 10 ) // Time will slow down if FPS<12.5 (125FPS / 10)
            {
                timeControl_.tick( FRAME_DELTA_TIME );
                gameStateManager_.update( FRAME_DELTA_TIME );
                if ( !graphicEngine_->run() )
                {
                    we_must_draw = false;
                    break;
                }
                // eventreceiver.setKeysLastState();
                next += FRAME_DELTA_TIME_IN_MS;
                we_must_draw = true;
                // if ( gameStateManager_.allFramesMustBeShown() )
                //     break;
                ++loops;
            }
            if ( we_must_draw )
            {
#ifdef _DEBUG_MODE
                // printFPS();
#endif
                gameStateManager_.draw();
            }
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
