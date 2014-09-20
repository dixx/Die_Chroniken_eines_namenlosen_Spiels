#include "StateStartup.h"
#include "Camera.h"
#include "Collision.h"
#include "Configuration.h"
#include "Constants.h"
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
    createLoadingScreenImage();
    createLoadingScreenText();
    fader_ = device_->getGUIEnvironment()->addInOutFader();
    transitTo( STARTING );
}



StateStartup::~StateStartup()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    loadingScreenImageFrame_->remove();
    loadingText_->remove();
    fader_->remove();
}



void StateStartup::start( f32 frameDeltaTime )
{
    if ( fader_->isReady() )
        transitTo( RUNNING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateStartup::update( f32 frameDeltaTime )
{
    switch( classCounter_ )
    {
        case 0:
#ifdef _DEBUG_MODE
            //loadingText_->setText( L"Lade Kammerjäger..." );
            DebugShapesManager::getInstance( device_->getVideoDriver() );
#endif
            break;
        case 1:
            //loadingText_->setText( L"Lade Zufälle..." );
            Zufall::getInstance().start( device_->getTimer()->getRealTime() );
            break;
        case 2:
            //loadingText_->setText( L"Lade Uhren..." );
            TimerManager::getInstance();
            break;
        case 3:
            //loadingText_->setText( L"Lade Schreibmaschine..." );
            Scripting::getInstance();
            break;
        case 4:
            //loadingText_->setText( L"Lade Klänge..." );
            Ton::getInstance( device_->getFileSystem() );
            break;
        case 5:
            //loadingText_->setText( L"Lade Zeigefinger..." );
            Mauspfeil::getInstance( device_ ).setCurrentArrow( Mauspfeil::MAUSPFEIL_UNSICHTBAR );
            break;
        case 6:
            //loadingText_->setText( L"Lade Zusammenstöße..." );
            Collision::getInstance( device_->getSceneManager() );
            break;
        case 7:
            //loadingText_->setText( L"Lade Dinge..." );
            ObjectManager::getInstance( device_ );
            break;
        case 8:
            //loadingText_->setText( L"Lade Wetter..." );
            Weather::getInstance( device_->getSceneManager() );
            break;
        case 9:
            //loadingText_->setText( L"Lade Fußboden..." );
            Ground::getInstance( device_ );
            break;
        case 10:
            //loadingText_->setText( L"Lade Auge..." );
            Camera::getInstance( device_->getSceneManager() );
            break;
        case 11:
            //loadingText_->setText( L"Lade Ego..." );
            Hero::getInstance( device_->getSceneManager() );
            break;
        case 12:
        {
            //loadingText_->setText( L"Lade Vergangenheit..." );
            SaveGames* savegame = new SaveGames( device_ );
            savegame->findNewest();
            delete savegame;
            break;
        }
        default:
            GameStateManager::getInstance().requestNewState( GameStateManager::MAIN_MENU );
            loadingText_->setText( L"" );
            transitTo( STOPPING );
            break;
    }
    classCounter_++;
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateStartup::shutdown( f32 frameDeltaTime )
{
    if ( fader_->isReady() )
        transitTo( STOPPED );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateStartup::draw()
{
    device_->getVideoDriver()->beginScene();
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateStartup::handleGuiEvents( const irr::SEvent& event )
{
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> event
    return false;
}
#pragma GCC diagnostic error "-Wunused-parameter"



/* private */



void StateStartup::createLoadingScreenImage()
{
    GenericHelperMethods::getInstance().validateFileExistence( "GFX/Schnellladebildschirm.jpg" );
    video::ITexture* loadingScreenImage = device_->getVideoDriver()->getTexture( "GFX/Schnellladebildschirm.jpg" );
    loadingScreenImageFrame_ = device_->getGUIEnvironment()->addImage(
            // set to screen center
            core::recti( core::dimension2di( 0, 0 ), Configuration::getInstance().getScreenSize() ) );
    loadingScreenImageFrame_->setImage( loadingScreenImage );
    // if image > screensize:
    loadingScreenImageFrame_->setScaleImage( true );
    loadingScreenImageFrame_->setEnabled( false );
}



void StateStartup::createLoadingScreenText()
{
    core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    GenericHelperMethods& helpers = GenericHelperMethods::getInstance( device_ );
    loadingText_ = device_->getGUIEnvironment()->addStaticText(
            L"",
            core::recti( core::dimension2di( 9, screenSize.Height - 30 ), screenSize )
    );
    loadingText_->setOverrideColor( video::SColor( 255, 128, 64, 64) );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.xml" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font.png" );
    helpers.validateFileExistence( "GFX/FONTS/Dooling_font_readme.txt" );
    gui::IGUIFont* font = device_->getGUIEnvironment()->getFont( "GFX/FONTS/Dooling_font.xml" );
    loadingText_->setOverrideFont( font );
}



void StateStartup::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            fader_->fadeIn( 900 );
            loadingScreenImageFrame_->setEnabled( true );
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
