#include "StateUnloadGameContent.h"
#include "Camera.h"
#include "Collision.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "GenericHelperMethods.h"
#include "Ground.h"
#include "Hero.h"
#include "Logfile.h"
#include "Mauspfeil.h"
#include "ObjectManager.h"
#include "Weather.h"



StateUnloadGameContent::StateUnloadGameContent( IrrlichtDevice* device )
: GameState(),
  device_(device),
  moduleCounter_(0)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [StateLoadGameContent] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Entlade..." );
    loadingScreen_ = new LoadingScreen( device_, io::path( "GFX/Ladebildschirm_v3.png" ) );
    forceDraw_ = true;
    transitTo( STARTING );
}



StateUnloadGameContent::~StateUnloadGameContent()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( loadingScreen_ )
        delete loadingScreen_;
}



void StateUnloadGameContent::start( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on startup
    transitTo( RUNNING );
}



void StateUnloadGameContent::update( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics
    switch( moduleCounter_ )
    {
        case 0:
            loadingScreen_->setText( L"Schließe Augen..." );
            Camera::getInstance().lockToNode( 0 );
            break;
        case 1:
            loadingScreen_->setText( L"Verliere Bewußtsein..." );
            Hero::getInstance().unload();
            break;
        case 2:
            loadingScreen_->setText( L"Werde dumm..." );
            //...fahre KI runter
            break;
        case 3:
            loadingScreen_->setText( L"Lasse alles los..." );
            ObjectManager::getInstance().unload();
            break;
        case 4:
            loadingScreen_->setText( L"Verliere Bodenständigkeit..." );
            Ground::getInstance().unload();
            break;
        case 5:
            loadingScreen_->setText( L"Gehe nach drinnen..." );
            Weather::getInstance().unload();
            break;
        case 6:
            loadingScreen_->setText( L"Vergiss das Gesehene..." );
            device_->getSceneManager()->getMeshCache()->clearUnusedMeshes();
            Collision::getInstance().clearRemainingSelectors();
            device_->getVideoDriver()->removeAllHardwareBuffers();
            device_->getVideoDriver()->removeAllTextures();
            break;
        default:
            loadingScreen_->setText( L"" );
            GameStateManager::getInstance().requestNewState( GameStateManager::MAIN_MENU );
            transitTo( STOPPING );
            break;
    }
    moduleCounter_++;
}



void StateUnloadGameContent::shutdown( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on shutdown
    transitTo( STOPPED );
}



void StateUnloadGameContent::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateUnloadGameContent::handleGuiEvents( const irr::SEvent& event )
{
    (void)event; // no event handling necessary here
    return false;
}



/* private */



void StateUnloadGameContent::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            loadingScreen_->enable();
            Eventreceiver::getInstance().setEventReactionActive( false, false, false );
            Mauspfeil::getInstance().setCurrentArrow( Mauspfeil::MAUSPFEIL_UNSICHTBAR );
            break;
        case RUNNING:
            currentInternalState_ = RUNNING;
            break;
        case STOPPING:
            currentInternalState_ = STOPPING;
            break;
        default:
            currentInternalState_ = STOPPED;
            break;
    }
}
