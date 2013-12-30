#include "GameFloatControl.h"
//#include "Camera.h"
//#include "Collision.h"
#include "Configuration.h"
#include "Constants.h"
#ifdef _DEBUG_MODE
//    #include "DebugShapesManager.h"
//    #include "Debugwindow.h"
#endif
#include "Eventreceiver.h"
//#include "GenericHelperMethods.h"
//#include "Ground.h"
//#include "Hero.h"
#include "Logfile.h"
//#include "Mauspfeil.h"
//#include "Menues.h"
//#include "ObjectManager.h"
//#include "Scripting.h"
//#include "TimerManager.h"
//#include "Ton.h"
//#include "Weather.h"
//#include "World.h"
//#include "Zufall.h"



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
    GameStateManager::getInstance( device_ ); // aktiviert INIT-State

#ifdef _DEBUG_MODE
//    DebugShapesManager::getInstance( device_->getVideoDriver() );
//    Debugwindow::getInstance( device_ );
#endif
//    GenericHelperMethods::getInstance( device_ );
//    TimerManager::getInstance();
//    Scripting::getInstance();
    // todo hier vielleicht Loadingscreen anzeigen?
//    ObjectManager::getInstance( device_ );
//    Collision::getInstance( device_->getSceneManager() );
//    Ton::getInstance( device_->getFileSystem() );
//    Mauspfeil::getInstance( device_ );
//    Weather::getInstance( device_->getSceneManager() );
//    Ground::getInstance( device_ );
//    Camera::getInstance( device_->getSceneManager() );
//    Hero::getInstance( device_->getSceneManager() );
//    World::getInstance();
//    Zufall::getInstance().start( device_->getTimer()->getRealTime() );
//    Menues::getInstance( device_ );
    // ...
//    Menues::getInstance().transitTo( Menues::MENUE_HAUPTMENUE );
    return SUCCEEDED;
}



void GameFloatControl::run()
{
    GameStateManager& gamestates = GameStateManager::getInstance();
    Eventreceiver& eventreceiver = Eventreceiver::getInstance();
    prepareFrameDeltaTime();
    while ( device_->run() )
    {
        if ( !device_->isWindowActive() )
            device_->yield();
        updateFrameDeltaTime();
        gamestates.getActiveState()->update( frameDeltaTime_ );
        eventreceiver.setKeysLastState();
        gamestates.getActiveState()->draw();
#ifdef _DEBUG_MODE
        printFPS();
#endif
    }
//    // lokale Kopien einiger Zeiger holen (aus Performance-Gruenden)
//    scene::ISceneManager* sceneManager = device_->getSceneManager();
//    video::IVideoDriver* videoDriver = device_->getVideoDriver();
//    gui::IGUIEnvironment* guiEnvironment = device_->getGUIEnvironment();
//    // einige Referenzen lokal holen (aus Performance-Gruenden)
//    Camera& camera = Camera::getInstance();
//    Eventreceiver& eventreceiver = Eventreceiver::getInstance();
//    Mauspfeil& mauspfeil = Mauspfeil::getInstance();
//    TimerManager& timermanager = TimerManager::getInstance();
//    World& world = World::getInstance();
//    Weather& weather = Weather::getInstance();
//#ifdef _DEBUG_MODE
//    DebugShapesManager& debugshapes = DebugShapesManager::getInstance();
//    Debugwindow& debugwindow = Debugwindow::getInstance();
//#endif
//    while ( device_->run() )
//    {
//        if ( !device_->isWindowActive() )
//            device_->yield();
//        updateFrameDeltaTime();
//        if ( gameIsRunning )
//            checkInputForGame();
//        if ( gameIsRunning )
//        {
//            timermanager.tick( frameDeltaTime_ );
//            world.update( frameDeltaTime_ );
//#ifdef _DEBUG_MODE
//            debugwindow.addLine( L"Cam above Ground: ",
//                    Ground::getInstance().getHeightFromPosition(
//                            camera.getCurrentPosition() ).Y );
//#endif
//        }
//#ifdef _DEBUG_MODE
//        debugwindow.addLine( L"Dreiecke: ",
//                videoDriver->getPrimitiveCountDrawn() );
//        debugwindow.show();
//        if ( eventreceiver.hasKeyJustBeenPressedDown( KEY_F1 ) )
//            debugwindow.toggle();
//#endif
//        eventreceiver.setKeysLastState();
//        videoDriver->beginScene( true, true, weather.getSkyColor() );
//        sceneManager->drawAll();
//        guiEnvironment->drawAll();
//#ifdef _DEBUG_MODE
//        debugshapes.drawAll();
//#endif
//        mauspfeil.draw();
//        videoDriver->endScene();
//        printFPS();
//    }
}



void GameFloatControl::stop()
{
    Logfile::getInstance().writeLine( Logfile::INFO, "" );
    Logfile::getInstance().writeLine( Logfile::INFO,
            "'Die Chroniken eines namenlosen Spiels' wurde normal beendet." );
    // device wird im dtor von Ablaufsteuerung gedropt.
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
            device_->getVideoDriver() );
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
    if ( lastFPS_ != fps_ )
    {
        core::stringw str = L"FPS:";
        str += fps_;
        device_->setWindowCaption( str.c_str() );
        lastFPS_ = fps_;
    }
}
#endif
