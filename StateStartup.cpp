#include "StateStartup.h"
#include "Camera.h"
#include "Collision.h"
//#include "Configuration.h"
//#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Ground.h"
#include "Hero.h"
#include "Logfile.h"
#include "Mauspfeil.h"
#include "ObjectManager.h"
#include "SaveGames.h"
#include "Scripting.h"
#include "TimerManager.h"
#include "Ton.h"
#include "Weather.h"
#include "Zufall.h"
#ifdef _DEBUG_MODE
#include "DebugShapesManager.h"
#endif



StateStartup::StateStartup( IrrlichtDevice* device )
: GameState(),
  device_(device),
  classCounter_(0)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [StateStartup] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Lade..." );
    GenericHelperMethods::getInstance( device_ );
    loadingScreen_ = new LoadingScreen( device_, io::path( "GFX/Schnellladebildschirm.jpg" ) );
    fader_ = device_->getGUIEnvironment()->addInOutFader();
    transitTo( STARTING );
}



StateStartup::~StateStartup()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( loadingScreen_ )
        delete loadingScreen_;
    fader_->remove();
}



void StateStartup::start( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on startup
    if ( fader_->isReady() )
        transitTo( RUNNING );
}



void StateStartup::update( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics
    switch( classCounter_ )
    {
        case 0:
#ifdef _DEBUG_MODE
            //loadingScreen_->setText( L"Lade Kammerjäger..." );
            DebugShapesManager::getInstance( device_->getVideoDriver() );
#endif
            break;
        case 1:
            //loadingScreen_->setText( L"Lade Zufälle..." );
            Zufall::getInstance().start( device_->getTimer()->getRealTime() );
            break;
        case 2:
            //loadingScreen_->setText( L"Lade Uhren..." );
            TimerManager::getInstance();
            break;
        case 3:
            //loadingScreen_->setText( L"Lade Schreibmaschine..." );
            Scripting::getInstance();
            break;
        case 4:
            //loadingScreen_->setText( L"Lade Klänge..." );
            Ton::getInstance( device_->getFileSystem() );
            break;
        case 5:
            //loadingScreen_->setText( L"Lade Zeigefinger..." );
            Mauspfeil::getInstance( device_ ).setCurrentArrow( Mauspfeil::MAUSPFEIL_UNSICHTBAR );
            break;
        case 6:
            //loadingScreen_->setText( L"Lade Zusammenstöße..." );
            Collision::getInstance( device_->getSceneManager() );
            break;
        case 7:
            //loadingScreen_->setText( L"Lade Dinge..." );
            ObjectManager::getInstance( device_ );
            break;
        case 8:
            //loadingScreen_->setText( L"Lade Wetter..." );
            Weather::getInstance( device_->getSceneManager() );
            break;
        case 9:
            //loadingScreen_->setText( L"Lade Fußboden..." );
            Ground::getInstance( device_ );
            break;
        case 10:
            //loadingScreen_->setText( L"Lade Auge..." );
            Camera::getInstance( device_->getSceneManager() );
            break;
        case 11:
            //loadingScreen_->setText( L"Lade Ego..." );
            Hero::getInstance( device_->getSceneManager() );
            break;
        case 12:
        {
            //loadingScreen_->setText( L"Lade Vergangenheit..." );
            SaveGames* savegame = new SaveGames( device_ );
            savegame->findNewest();
            delete savegame;
            break;
        }
        default:
            GameStateManager::getInstance().requestNewState( GameStateManager::MAIN_MENU );
            loadingScreen_->setText( L"" );
            transitTo( STOPPING );
            break;
    }
    classCounter_++;
}



void StateStartup::shutdown( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on shutdown
    if ( fader_->isReady() )
        transitTo( STOPPED );
}



void StateStartup::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateStartup::handleGuiEvents( const irr::SEvent& event )
{
    (void)event; // no event handling necessary here
    return false;
}



/* private */



void StateStartup::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            fader_->fadeIn( 900 );
            loadingScreen_->enable();
            break;
        case RUNNING:
            currentInternalState_ = RUNNING;
            break;
        case STOPPING:
            currentInternalState_ = STOPPING;
            fader_->fadeOut( 900 );
            break;
        default:
            currentInternalState_ = STOPPED;
            break;
    }
}
