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
    pictures_[CONCEPT_1] =      new LoadingScreen( device_, io::path( "GFX/Konzept1.png" ) );
    pictures_[CONCEPT_2] =      new LoadingScreen( device_, io::path( "GFX/Konzept2.png" ) );
    pictures_[CONCEPT_3] =      new LoadingScreen( device_, io::path( "GFX/Konzept3.png" ) );
    pictures_[CONCEPT_4] =      new LoadingScreen( device_, io::path( "GFX/Konzept4.png" ) );
    pictures_[CONCEPT_5] =      new LoadingScreen( device_, io::path( "GFX/Konzept5.png" ) );
    pictures_[CONCEPT_6] =      new LoadingScreen( device_, io::path( "GFX/Konzept6.png" ) );
    pictures_[CONCEPT_7] =      new LoadingScreen( device_, io::path( "GFX/Konzept7.png" ) );
    pictures_[CONCEPT_8] =      new LoadingScreen( device_, io::path( "GFX/Konzept8.png" ) );
    forceDraw_ = true;
    transitTo( STARTING );
}



StateLoadGameContent::~StateLoadGameContent()
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
            pictures_[LOADING_SCREEN]->setText( L"Lade Sonnenschein..." );
            Weather::getInstance().load();
            pictures_[ICON_WEATHER]->enable();
            break;
        case 1:
            pictures_[LOADING_SCREEN]->setText( L"Lade Fußboden..." );
            Ground::getInstance().load( ( levelName_ + ".map" ).c_str() );
            pictures_[ICON_WORLD]->enable();
            break;
        case 2:
            pictures_[LOADING_SCREEN]->setText( L"Lade hübsche Dinge..." );
            //ObjectManager::getInstance().loadBasicDecorations();
            pictures_[ICON_FLORA]->enable();
            break;
        case 3:
            pictures_[LOADING_SCREEN]->setText( L"Lade feste Dinge..." );
            ObjectManager::getInstance().loadSolids( ( levelName_ + ".solids" ).c_str() );
            pictures_[ICON_BUILDINGS]->enable();
            break;
        case 4:
            pictures_[LOADING_SCREEN]->setText( L"Lade zappelnde Dinge..." );
            ObjectManager::getInstance().loadNPCs( ( levelName_ + ".npcs" ).c_str() );
            pictures_[ICON_PEOPLE]->enable();
            break;
        case 5:
            pictures_[LOADING_SCREEN]->setText( L"Lade Würfelmaschine..." );
            // ...initialisiere KI
            pictures_[ICON_QUESTS]->enable();
            break;
        case 6:
            pictures_[LOADING_SCREEN]->setText( L"Lade das Wichtigste von allem..." );
            Hero::getInstance().load(); //TODO später aus Savegame laden!
            pictures_[ICON_HERO]->enable();
            break;
        case 7:
            pictures_[LOADING_SCREEN]->setText( L"Lade Augen..." );
            Camera::getInstance().lockToNode( Hero::getInstance().current()->nodeInterface() );
            pictures_[ICON_FAUNA]->enable();
            break;
        default:
            pictures_[LOADING_SCREEN]->setText( L"" );
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
            pictures_[LOADING_SCREEN]->enable();
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
