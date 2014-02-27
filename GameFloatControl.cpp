#include "GameFloatControl.h"
#include "Configuration.h"
#include "Constants.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "Logfile.h"
#include "TimerManager.h"
#ifdef _DEBUG_MODE
#include "Debugwindow.h"
#endif


GameFloatControl& GameFloatControl::getInstance()
{
    static GameFloatControl _instance;
    return _instance;
}



bool GameFloatControl::start()
{
    device_ = createDevice( video::EDT_NULL );
    if ( device_ == 0 )
        return FAILED;
    createLogfile();
    readConfig();
    device_->drop();
    if ( createDeviceFromConfig() == FAILED )
        return FAILED;
    GameStateManager::getInstance( device_ );
#ifdef _DEBUG_MODE
    Debugwindow::getInstance( device_ );
#endif
    return SUCCEEDED;
}



void GameFloatControl::run()
{
    GameStateManager& game = GameStateManager::getInstance();
    Eventreceiver& eventreceiver = Eventreceiver::getInstance();
    prepareFrameDeltaTime();
    while ( device_->run() )
    {
        if ( !device_->isWindowActive() )
            device_->yield();
        updateFrameDeltaTime();
        TimerManager::getInstance().tick( frameDeltaTime_ );
        game.update( frameDeltaTime_ );
        eventreceiver.setKeysLastState();
#ifdef _DEBUG_MODE
        printFPS();
#endif
        game.draw();
    }
}



void GameFloatControl::stop()
{
    Logfile::getInstance().writeLine( Logfile::INFO, "" );
    Logfile::getInstance().writeLine( Logfile::INFO,
            "'Die Chroniken eines namenlosen Spiels' wurde normal beendet." );
}



/* private */



GameFloatControl::GameFloatControl()
: device_(0),
  now_(0),
  then_(0),
  frameDeltaTime_(0.0f)
#ifdef _DEBUG_MODE
  ,fps_(0)
  ,lastFPS_(0)
#endif
{
    ;
}



GameFloatControl::~GameFloatControl()
{
    if ( device_ )
    {
        device_->drop();
        device_ = 0;
    }
}



void GameFloatControl::createLogfile()
{
    Logfile::getInstance( device_->getFileSystem(),
#ifdef _DEBUG_MODE
    "debug.log", Logfile::DEBUG );
#else
    "game.log", Logfile::INFO );
#endif
}



void GameFloatControl::readConfig()
{
    Configuration::getInstance( device_->getFileSystem() ).readConfigFile(
            "CONFIG.CFG" );
}



bool GameFloatControl::createDeviceFromConfig()
{
    Logfile& logfile = Logfile::getInstance();
    Configuration& config = Configuration::getInstance();
    Eventreceiver::getInstance().setEventReactionActive( false, false, false );
    device_ = createDevice(
            config.getRenderMode(),
            config.getScreenSize(),
            config.getColorDepht(),
            config.isFullScreen(),
            true,
            config.isFullScreen(),
            &Eventreceiver::getInstance()
    );
    if ( device_ == 0 )
        return FAILED;
    logfile.setNewFilesystem( device_->getFileSystem() );
    config.setNewFilesystem( device_->getFileSystem() );
    logfile.writeLine( Logfile::DETAIL, "3D-Entchen erfolgreich erstellt." );
    logfile.writeLine( Logfile::DETAIL, "    Version: IrrLicht ",
            device_->getVersion() );
    logfile.writeLine( Logfile::DETAIL, "    Treiber: ",
            device_->getVideoDriver()->getName() );
    device_->getCursorControl()->setVisible( false );
    device_->getVideoDriver()->beginScene( true, false, COL_BLACK );
    device_->getVideoDriver()->endScene();
    return SUCCEEDED;
 }



void GameFloatControl::prepareFrameDeltaTime()
{
    then_ = device_->getTimer()->getTime();
}



void GameFloatControl::updateFrameDeltaTime()
{
    now_ = device_->getTimer()->getTime();
    frameDeltaTime_ = ( now_ != then_ )
                    ? static_cast<f32>( now_ - then_ ) * 0.001f
                    : core::ROUNDING_ERROR_f32;
    then_ = now_;
}



#ifdef _DEBUG_MODE
void GameFloatControl::printFPS()
{
    fps_ = device_->getVideoDriver()->getFPS();
    //if ( lastFPS_ != fps_ )
    {
        core::stringw str = L"FPS:";
        str += fps_;
        Debugwindow::getInstance().addLine( str.c_str() );
        lastFPS_ = fps_;
    }
}
#endif
