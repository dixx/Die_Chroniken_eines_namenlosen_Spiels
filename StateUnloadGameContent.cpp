#include "StateUnloadGameContent.h"
#include "Camera.h"
#include "Collision.h"
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



StateUnloadGameContent::StateUnloadGameContent( IrrlichtDevice* device )
: GameState(),
  device_(device),
  moduleCounter_(0)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [StateLoadGameContent] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Entlade..." );
    createLoadingScreenImage();
    createLoadingScreenText();
    transitTo( STARTING );
}



StateUnloadGameContent::~StateUnloadGameContent()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    loadingScreenImageFrame_->remove();
    loadingText_->remove();
}



void StateUnloadGameContent::start( f32 frameDeltaTime )
{
    transitTo( RUNNING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateUnloadGameContent::update( f32 frameDeltaTime )
{
    switch( moduleCounter_ )
    {
        case 0:
            loadingText_->setText( L"Schließe Augen..." );
            Camera::getInstance().lockToNode( 0 );
            break;
        case 1:
            loadingText_->setText( L"Verliere Bewußtsein..." );
            Hero::getInstance().unload();
            break;
        case 2:
            loadingText_->setText( L"Werde dumm..." );
            //...fahre KI runter
            break;
        case 3:
            loadingText_->setText( L"Lasse alles los..." );
            ObjectManager::getInstance().unload();
            break;
        case 4:
            loadingText_->setText( L"Verliere Bodenständigkeit..." );
            Ground::getInstance().unload();
            break;
        case 5:
            loadingText_->setText( L"Gehe nach drinnen..." );
            Weather::getInstance().unload();
            break;
        case 6:
            loadingText_->setText( L"Vergiss das Gesehene..." );
            device_->getSceneManager()->getMeshCache()->clearUnusedMeshes();
            Collision::getInstance().clearRemainingSelectors();
            device_->getVideoDriver()->removeAllHardwareBuffers();
            loadingScreenImageFrame_->getImage()->grab();
            device_->getVideoDriver()->removeAllTextures();
            loadingScreenImageFrame_->getImage()->drop();
            break;
        default:
            loadingText_->setText( L"" );
            GameStateManager::getInstance().requestNewState(
                    GameStateManager::MAIN_MENU );
            transitTo( STOPPING );
            break;
    }
    moduleCounter_++;
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateUnloadGameContent::shutdown( f32 frameDeltaTime )
{
    transitTo( STOPPED );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateUnloadGameContent::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateUnloadGameContent::handleGuiEvents( const irr::SEvent& event )
{
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> event
    return false;
}
#pragma GCC diagnostic error "-Wunused-parameter"



/* private */



void StateUnloadGameContent::createLoadingScreenImage()
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



void StateUnloadGameContent::createLoadingScreenText()
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



void StateUnloadGameContent::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            loadingScreenImageFrame_->setEnabled( true );
            Eventreceiver::getInstance().setEventReactionActive(
                    false, false, false );
            Mauspfeil::getInstance().setCurrentArrow(
                    Mauspfeil::MAUSPFEIL_UNSICHTBAR );
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
