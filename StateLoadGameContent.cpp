#include "StateLoadGameContent.h"
#include "Camera.h"
#include "Configuration.h"
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
        Logfile::getInstance().emergencyExit(
                "Entchen in [StateLoadGameContent] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Lade..." );
    createLoadingScreenImage();
    createLoadingScreenText();
    transitTo( STARTING );
}



StateLoadGameContent::~StateLoadGameContent()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    loadingScreenImageFrame_->remove();
    loadingText_->remove();
}



void StateLoadGameContent::start( f32 frameDeltaTime )
{
    transitTo( RUNNING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateLoadGameContent::update( f32 frameDeltaTime )
{
    switch( moduleCounter_ )
    {
        case 0:
            loadingText_->setText( L"Lade Sonnenschein..." );
            Weather::getInstance().load();
            break;
        case 1:
            loadingText_->setText( L"Lade Fußboden..." );
            Ground::getInstance().load( ( levelName_ + ".map" ).c_str() );
            break;
        case 2:
            loadingText_->setText( L"Lade hübsche Dinge..." );
            //ObjectManager::getInstance().loadBasicDecorations();
            break;
        case 3:
            loadingText_->setText( L"Lade feste Dinge..." );
            ObjectManager::getInstance().loadSolids(
                    ( levelName_ + ".solids" ).c_str() );
            break;
        case 4:
            loadingText_->setText( L"Lade zappelnde Dinge..." );
            ObjectManager::getInstance().loadNPCs(
                    ( levelName_ + ".npcs" ).c_str() );
            break;
        case 5:
            loadingText_->setText( L"Lade Würfelmaschine..." );
            // ...initialisiere KI
            break;
        case 6:
            loadingText_->setText( L"Lade das Wichtigste von allem..." );
            Hero::getInstance().load(); //TODO später aus Savegame laden!
            break;
        case 7:
            loadingText_->setText( L"Lade Augen..." );
            Camera::getInstance().lockToNode(
                    Hero::getInstance().current()->nodeInterface() );
            break;
        default:
            loadingText_->setText( L"" );
            GameStateManager::getInstance().requestNewState(
                    GameStateManager::GAME );
            transitTo( STOPPING );
            break;
    }
    moduleCounter_++;
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateLoadGameContent::shutdown( f32 frameDeltaTime )
{
    transitTo( STOPPED );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateLoadGameContent::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateLoadGameContent::handleGuiEvents( const irr::SEvent& event )
{
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> event
    return false;
}
#pragma GCC diagnostic error "-Wunused-parameter"



/* private */



void StateLoadGameContent::createLoadingScreenImage()
{
    GenericHelperMethods::getInstance().validateFileExistence(
            "GFX/Spiellogo.png" );
    video::ITexture* loadingScreenImage = device_->getVideoDriver()->getTexture(
            "GFX/Spiellogo.png" );
    loadingScreenImageFrame_ = device_->getGUIEnvironment()->addImage(
            core::recti(
                    core::dimension2di( 0, 0 ),
                    Configuration::getInstance().getScreenSize()
            )
    );
    loadingScreenImageFrame_->setImage( loadingScreenImage );
    loadingScreenImageFrame_->setScaleImage( true );
    loadingScreenImageFrame_->setEnabled( false );
}



void StateLoadGameContent::createLoadingScreenText()
{
    core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    GenericHelperMethods& helpers = GenericHelperMethods::getInstance( device_ );
    loadingText_ = device_->getGUIEnvironment()->addStaticText(
            L"",
            core::recti(
                    core::dimension2di( 9, screenSize.Height - 30 ),
                    screenSize
            )
    );
    loadingText_->setOverrideColor( video::SColor( 255, 128, 64, 64) );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.xml" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.png" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font_readme.txt" );
    gui::IGUIFont* font = device_->getGUIEnvironment()->getFont(
            "GFX/FONTS/Dooling_font.xml" );
    loadingText_->setOverrideFont( font );
}



void StateLoadGameContent::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            Eventreceiver::getInstance().setEventReactionActive(
                    false, false, false );
            Mauspfeil::getInstance().setCurrentArrow(
                    Mauspfeil::MAUSPFEIL_UNSICHTBAR );
            loadingScreenImageFrame_->setEnabled( true );
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
