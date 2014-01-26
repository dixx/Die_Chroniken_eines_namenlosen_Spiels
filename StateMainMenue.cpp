#include "StateMainMenue.h"
#include "Configuration.h"
#include "Constants.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "GenericHelperMethods.h"
#include "Mauspfeil.h"
#include "Logfile.h"



StateMainMenue::StateMainMenue( IrrlichtDevice* device )
: GameState(),
  device_(device),
  driver_(0),
  menueScreenImageCatalogue_(0),
  mainMenueTexture_(0),
  mainMenueBgColor_(video::SColor( 255, 248, 245, 240 ))
{
    if ( device_ == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [StateMainMenue] nicht mehr gefunden! Abbruch." );
    driver_ = device_->getVideoDriver();
    device_->setWindowCaption( L"Die Chroniken eines namenlosen Spiels" );
    loadTextures();
    extractImagesFromCatalogue();
    createMainMenu();
    transitTo( STARTING );
}



StateMainMenue::~StateMainMenue()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
}



void StateMainMenue::start( f32 frameDeltaTime )
{
    transitTo( RUNNING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateMainMenue::update( f32 frameDeltaTime )
{
    if ( Eventreceiver::getInstance().hasKeyJustBeenReleased( KEY_ESCAPE ) )
    {
        GameStateManager::getInstance().requestNewState(
                            GameStateManager::SHUTDOWN );
        transitTo( STOPPING );
    }
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateMainMenue::shutdown( f32 frameDeltaTime )
{
    transitTo( STOPPED );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateMainMenue::draw()
{
    device_->getVideoDriver()->beginScene( true, false, mainMenueBgColor_ );
    //device_->getSceneManager()->drawAll();
    device_->getGUIEnvironment()->drawAll();
    Mauspfeil::getInstance().draw();
    device_->getVideoDriver()->endScene();
}



bool StateMainMenue::handleGuiEvents()
{
    return false;
}



/* private */



void StateMainMenue::transitTo( internalState state )
{
    switch ( state )
    {
        case STARTING:
            currentInternalState_ = STARTING;
            break;
        case RUNNING:
            Eventreceiver::getInstance().setEventReactionActive(
                    true, true, true );
            Mauspfeil::getInstance().setCurrentArrow(
                    Mauspfeil::MAUSPFEIL_SELECT );
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



void StateMainMenue::loadTextures()
{
    GenericHelperMethods& helper = GenericHelperMethods::getInstance();
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false );
    helper.validateFileExistence( "GFX/menues1.bmp" );
    menueScreenImageCatalogue_ = driver_->getTexture( "GFX/menues1.bmp" );
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, true );
}



void StateMainMenue::extractImagesFromCatalogue()
{
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false );
    driver_->disableFeature( video::EVDF_BILINEAR_FILTER, true );
    video::IImage* wholeImage = driver_->createImageFromFile(
            menueScreenImageCatalogue_->getName() );
    if ( !wholeImage )
        Logfile::getInstance().emergencyExit( "Bild nicht geladen!" );
    // Ausschneiden des mainMenue-Hintergrundbildes als eigene Textur
    core::dimension2du menueTextureSize = core::dimension2du( 436, 555 );
    video::IImage* partialImage = driver_->createImage(
            wholeImage->getColorFormat(), menueTextureSize );
    wholeImage->copyTo(
            partialImage,
            core::position2di( 0, 0 ),
            core::recti( core::position2di( 588, 212 ), menueTextureSize )
    );
    mainMenueTexture_ = driver_->addTexture(
            "GFX/mainMenueTexture.virtual", partialImage );
    partialImage->drop();
    driver_->makeColorKeyTexture( mainMenueTexture_, COL_MAGICPINK );
    wholeImage->drop();
    driver_->disableFeature( video::EVDF_BILINEAR_FILTER, false );
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, true );
}



void StateMainMenue::createMainMenu()
{
    gui::IGUIEnvironment* guienv = device_->getGUIEnvironment();
    u32 texWidth = mainMenueTexture_->getSize().Width;
    u32 texHeight = mainMenueTexture_->getSize().Height;
    core::dimension2du screen = Configuration::getInstance().getScreenSize();

    gui::IGUIElement* root = guienv->getRootGUIElement();

    gui::IGUIImage* menueBgImage = guienv->addImage(
            core::recti(
                    screen.Width - 20 - texWidth ,
                    screen.Height - 20 - texHeight,
                    screen.Width - 20,
                    screen.Height - 20
            ),  // Abmessungen auf Bildschirm
            root,  // parent
            1  // id
    );
    menueBgImage->setImage( mainMenueTexture_ );
}
