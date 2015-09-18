#include "StateLoadGameContent.h"
#include "Camera.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "GenericHelperMethods.h"
#include "Ground.h"
#include "Hero.h"
#include "Logfile.h"
#include "Mauspfeil.h"
#include "ObjectManager.h"
#include "Weather.h"



StateLoadGameContent::StateLoadGameContent( IrrlichtDevice* device )
: GameState(),
  device_(device),
  levelName_("GFX/LEVELS/Level_X"),
  moduleCounter_(0)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [StateLoadGameContent] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Lade..." );
    loadingScreen_ = new LoadingScreen( device_, io::path( "GFX/Ladebildschirm_v3.png" ) );
    forceDraw_ = true;
    transitTo( STARTING );
}



StateLoadGameContent::~StateLoadGameContent()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    if ( loadingScreen_ )
        delete loadingScreen_;
}



void StateLoadGameContent::start( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on startup
    transitTo( RUNNING );
}



void StateLoadGameContent::update( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics
    switch( moduleCounter_ )
    {
        case 0:
            loadingScreen_->setText( L"Lade Sonnenschein..." );
            Weather::getInstance().load();
            break;
        case 1:
            loadingScreen_->setText( L"Lade Fußboden..." );
            Ground::getInstance().load( ( levelName_ + ".map" ).c_str() );
            break;
        case 2:
            loadingScreen_->setText( L"Lade hübsche Dinge..." );
            //ObjectManager::getInstance().loadBasicDecorations();
            break;
        case 3:
            loadingScreen_->setText( L"Lade feste Dinge..." );
            ObjectManager::getInstance().loadSolids( ( levelName_ + ".solids" ).c_str() );
            break;
        case 4:
            loadingScreen_->setText( L"Lade zappelnde Dinge..." );
            ObjectManager::getInstance().loadNPCs( ( levelName_ + ".npcs" ).c_str() );
            break;
        case 5:
            loadingScreen_->setText( L"Lade Würfelmaschine..." );
            // ...initialisiere KI
            break;
        case 6:
            loadingScreen_->setText( L"Lade das Wichtigste von allem..." );
            Hero::getInstance().load(); //TODO später aus Savegame laden!
            break;
        case 7:
            loadingScreen_->setText( L"Lade Augen..." );
            Camera::getInstance().lockToNode( Hero::getInstance().current()->nodeInterface() );
            break;
        default:
            loadingScreen_->setText( L"" );
            GameStateManager::getInstance().requestNewState( GameStateManager::GAME );
            transitTo( STOPPING );
            break;
    }
    moduleCounter_++;
}



void StateLoadGameContent::shutdown( f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on shutdown
    transitTo( STOPPED );
}



void StateLoadGameContent::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateLoadGameContent::handleGuiEvents( const irr::SEvent& event )
{
    (void)event; // no event handling necessary here
    return false;
}



/* private */



void StateLoadGameContent::transitTo( internalState state )
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
