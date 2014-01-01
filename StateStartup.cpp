#include "StateStartup.h"
#include "Configuration.h"
#include "Constants.h"
#include "GenericHelperMethods.h"
#include "Logfile.h"
//#include "Camera.h"
//#include "Collision.h"
//#include "Eventreceiver.h"
//#include "Ground.h"
//#include "Hero.h"
#include "Mauspfeil.h"
//#include "ObjectManager.h"
#include "Scripting.h"
#include "TimerManager.h"
#include "Ton.h"
//#include "Weather.h"
//#include "World.h"
#include "Zufall.h"
#ifdef _DEBUG_MODE
#include "DebugShapesManager.h"
#include "Debugwindow.h"
#endif



StateStartup::StateStartup( IrrlichtDevice* device)
: GameState(),
  device_(device),
  classCounter_(0)
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [StateStartup] nicht mehr gefunden! Abbruch." );
    device_->setWindowCaption( L"Loading..." );
    GenericHelperMethods::getInstance( device_ );
    createLoadingScreenImage();
    createLoadingScreenText();
}



StateStartup::~StateStartup()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



#pragma GCC diagnostic ignored "-Wunused-parameter"
void StateStartup::update( f32 frameDeltaTime )
{
    switch( classCounter_ )
    {
        case 0:
#ifdef _DEBUG_MODE
            loadingText_->setText( L"Lade Kammerjäger..." );
            DebugShapesManager::getInstance( device_->getVideoDriver() );
            Debugwindow::getInstance( device_ );
#endif
            break;
        case 1:
            loadingText_->setText( L"Lade Zufälle..." );
            Zufall::getInstance().start( device_->getTimer()->getRealTime() );
            break;
        case 2:
            loadingText_->setText( L"Lade Zeitverwaltung..." );
            TimerManager::getInstance();
            break;
        case 3:
            loadingText_->setText( L"Lade Schreibmaschine..." );
            Scripting::getInstance();
            break;
        case 4:
            loadingText_->setText( L"Lade Klänge..." );
            Ton::getInstance( device_->getFileSystem() );
            break;
        case 5:
            loadingText_->setText( L"Lade Zeigefinger..." );
            Mauspfeil::getInstance( device_ );
            break;
            // wer benötigt wen zum Laden und Zerstören:
            //    Collision::getInstance( scenemanager );
            //    Weather::getInstance( scenemanager );
            //    ObjectManager::getInstance( device ); --> Collision
            //
            //    Ground::getInstance( device ); --> ObjectManager, Collision
            //    Camera::getInstance( scenemanager ); --> Ground
            //    Hero::getInstance( scenemanager ); --> Ground, ObjectManager
            //    World::getInstance(); --> alles
            // todo refactor or even remove Menues!
                //Menues::getInstance( device ); --> World
                // ...
                //Menues::getInstance().transitTo( Menues::MENUE_HAUPTMENUE );
        default:
            classCounter_ = 0;
            return;
            // change active gamestate
            break;
    }
    classCounter_++;
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateStartup::draw()
{
    device_->getVideoDriver()->beginScene( true, true, COL_BLACK );
    device_->getGUIEnvironment()->drawAll();
    device_->getVideoDriver()->endScene();
}



bool StateStartup::handleGuiEvents()
{
    return false;
}



/* private */



void StateStartup::createLoadingScreenImage()
{
    GenericHelperMethods::getInstance().validateFileExistence(
            "GFX/Spiellogo.png" );
    video::ITexture* loadingScreenImage = device_->getVideoDriver()->getTexture(
            "GFX/Spiellogo.png" );
    gui::IGUIImage* loadingScreenImageFrame =
            device_->getGUIEnvironment()->addImage(
                    core::recti( core::dimension2di( 0, 0 ),
                            Configuration::getInstance().getScreenSize() ) );
    loadingScreenImageFrame->setImage( loadingScreenImage );
    loadingScreenImageFrame->setScaleImage( true );
}



void StateStartup::createLoadingScreenText()
{
    core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    GenericHelperMethods& helpers = GenericHelperMethods::getInstance( device_ );
    loadingText_ = device_->getGUIEnvironment()->addStaticText(
            L"Lade Klassen...",
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
