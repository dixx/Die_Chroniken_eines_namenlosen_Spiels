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
    pictures_ = core::array<LoadingScreen*>( COUNT );
    pictures_[LOADING_SCREEN] = new LoadingScreen( device_, io::path( "GFX/Ladebildschirm_v3.png" ) );
    pictures_[ICON_WORLD] =     new LoadingScreen( device_, io::path( "GFX/Welt_icon.png" ) );
    pictures_[ICON_QUESTS] =    new LoadingScreen( device_, io::path( "GFX/Questfortschritt_icon.png" ) );
    pictures_[ICON_PEOPLE] =    new LoadingScreen( device_, io::path( "GFX/Bevoelkerung_icon.png" ) );
    pictures_[ICON_BUILDINGS] = new LoadingScreen( device_, io::path( "GFX/Gebaeude_icon.png" ) );
    pictures_[ICON_THINGS] =    new LoadingScreen( device_, io::path( "GFX/Gegenstaende_icon.png" ) );
    pictures_[ICON_HERO] =      new LoadingScreen( device_, io::path( "GFX/Held_icon.png" ) );
    pictures_[ICON_FLORA] =     new LoadingScreen( device_, io::path( "GFX/Pflanzen_icon.png" ) );
    pictures_[ICON_FAUNA] =     new LoadingScreen( device_, io::path( "GFX/Tiere_icon.png" ) );
    pictures_[ICON_WEATHER] =   new LoadingScreen( device_, io::path( "GFX/Wetter_icon.png" ) );
    for ( register u32 i = CONCEPT_1; i <= CONCEPT_8; ++i )
        pictures_[i] = 0;
    forceDraw_ = true;
    transitTo( STARTING );
}



StateUnloadGameContent::~StateUnloadGameContent()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    for ( register u32 i = 0; i < COUNT; ++i )
    {
        if ( pictures_[ i ] )
        {
            delete pictures_[ i ];
            pictures_[ i ] = 0;
        }
    }
    pictures_.clear();
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
            pictures_[LOADING_SCREEN]->setText( L"Schließe Augen..." );
            Camera::getInstance().followNode( 0 );
            break;
        case 1:
            pictures_[LOADING_SCREEN]->setText( L"Verliere Bewußtsein..." );
            Hero::getInstance().unload();
            pictures_[ICON_HERO]->disable();
            break;
        case 2:
            pictures_[LOADING_SCREEN]->setText( L"Werde dumm..." );
            //...fahre KI runter
            pictures_[ICON_QUESTS]->disable();
            break;
        case 3:
            pictures_[LOADING_SCREEN]->setText( L"Lasse alles los..." );
            ObjectManager::getInstance().unload();
            pictures_[ICON_PEOPLE]->disable();
            pictures_[ICON_FAUNA]->disable();
            pictures_[ICON_BUILDINGS]->disable();
            pictures_[ICON_THINGS]->disable();
            pictures_[ICON_FLORA]->disable();
            break;
        case 4:
            pictures_[LOADING_SCREEN]->setText( L"Verliere Bodenständigkeit..." );
            Ground::getInstance().unload();
            pictures_[ICON_WORLD]->disable();
            break;
        case 5:
            pictures_[LOADING_SCREEN]->setText( L"Gehe nach drinnen..." );
            Weather::getInstance().unload();
            pictures_[ICON_WEATHER]->disable();
            break;
        case 6:
            pictures_[LOADING_SCREEN]->setText( L"Vergiss das Gesehene..." );
            device_->getSceneManager()->getMeshCache()->clearUnusedMeshes();
            Collision::getInstance().clearRemainingSelectors();
            device_->getVideoDriver()->removeAllHardwareBuffers();
            device_->getVideoDriver()->removeAllTextures();
            break;
        default:
            pictures_[LOADING_SCREEN]->setText( L"" );
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
            for ( register u32 i = LOADING_SCREEN; i <= ICON_WEATHER; ++i )
                pictures_[i]->enable();
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
