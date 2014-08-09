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
    static GameFloatControl instance;
    return instance;
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

    const f32 FRAME_DELTA_TIME = 0.008f;  // 0.008s ~= 125 FPS fixed
    const u32 FRAME_DELTA_TIME_IN_MS = static_cast<u32>( FRAME_DELTA_TIME / 1000.f );

    u32 loops;
    bool we_must_draw;
    u32 next = device_->getTimer()->getTime();
    while ( device_->run() )
    {
        if ( !device_->isWindowActive() )
            device_->yield();
        loops = 0;
        we_must_draw = false;
        while ( device_->getTimer()->getTime() > next && loops < 10 ) // Time will slow down if FPS<12.5 (125FPS / 10)
        {
            TimerManager::getInstance().tick( FRAME_DELTA_TIME );
            game.update( FRAME_DELTA_TIME );
            eventreceiver.setKeysLastState();
            next += FRAME_DELTA_TIME_IN_MS;
            loops++;
            we_must_draw = true;
        }
#ifdef _DEBUG_MODE
        printFPS();
#endif
        if ( we_must_draw )
            game.draw();
        else
            device_->sleep( next - device_->getTimer()->getTime() );
    }
}



void GameFloatControl::stop()
{
    Logfile::getInstance().writeLine( Logfile::INFO, "" );
    Logfile::getInstance().writeLine( Logfile::INFO, "'Die Chroniken eines namenlosen Spiels' wurde normal beendet." );
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
    Configuration::getInstance( device_->getFileSystem() ).readConfigFile( "CONFIG.CFG" );
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
    logfile.writeLine( Logfile::DETAIL, "    Version: IrrLicht ", device_->getVersion() );
    logfile.writeLine( Logfile::DETAIL, "    Treiber: ", device_->getVideoDriver()->getName() );
    device_->getCursorControl()->setVisible( false );
    device_->getVideoDriver()->beginScene( true, false, COL_BLACK );
    device_->getVideoDriver()->endScene();
    return SUCCEEDED;
 }



void GameFloatControl::prepareFrameDeltaTime()
{
    then_ = device_->getTimer()->getTime();
}



#ifdef _DEBUG_MODE
void GameFloatControl::printFPS()
{
    fps_ = device_->getVideoDriver()->getFPS();
    {
        core::stringw str = L"FPS:";
        str += fps_;
        Debugwindow::getInstance().addLine( str.c_str() );
        lastFPS_ = fps_;
    }
}
#endif
