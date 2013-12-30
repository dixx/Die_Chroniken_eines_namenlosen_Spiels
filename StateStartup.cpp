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
//#include "Mauspfeil.h"
//#include "ObjectManager.h"
//#include "Scripting.h"
//#include "TimerManager.h"
//#include "Ton.h"
//#include "Weather.h"
//#include "World.h"
#include "Zufall.h"
#ifdef _DEBUG_MODE
//#include "DebugShapesManager.h"
//#include "Debugwindow.h"
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
    // todo create class that loads all needed fonts!
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
            loadingText_->setText( L"Lade Zufall..." );
            Zufall::getInstance().start( device_->getTimer()->getRealTime() );
            break;
            //#ifdef _DEBUG_MODE
            //    DebugShapesManager::getInstance( driver );
            //    Debugwindow::getInstance( device );
            //#endif
            //    GenericHelperMethods::getInstance( device );
            //    TimerManager::getInstance();
            //    Scripting::getInstance();
            //    ObjectManager::getInstance( device );
            //    Collision::getInstance( scenemanager );
            //    Ton::getInstance( filesystem );
            //    Mauspfeil::getInstance( device );
            //    Weather::getInstance( scenemanager );
            //    Ground::getInstance( device );
            //    Camera::getInstance( scenemanager );
            //    Hero::getInstance( scenemanager );
            //    World::getInstance();
            // todo refactor or even remove Menues!
                //Menues::getInstance( device );
                // ...
                //Menues::getInstance().transitTo( Menues::MENUE_HAUPTMENUE );
        default:
            classCounter_ = 0;
            // change active gamestate
            break;
    }
    classCounter_++;
    //frameDeltaTime += 1.0f;
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
    helpers.validateFileExistence( "GFX/Dooling_font.xml" );
    helpers.validateFileExistence( "GFX/Dooling_font.png" );
    helpers.validateFileExistence( "GFX/Dooling_font_readme.txt" );
    gui::IGUIFont* font = device_->getGUIEnvironment()->getFont(
            "GFX/Dooling_font.xml" );
    loadingText_->setOverrideFont( font );
}
