#include "StateMainMenue.h"
#include "Configuration.h"
#include "Constants.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "GenericHelperMethods.h"
#include "Mauspfeil.h"
#include "Logfile.h"
#include "Ton.h"



StateMainMenue::StateMainMenue( IrrlichtDevice* device )
: GameState(),
  device_(device),
  driver_(0),
  menueScreenImageCatalogue_(0),
  mainMenueTexture_(0),
  mainMenueBgColor_(video::SColor( 255, 248, 245, 240 )),
  callerID_(0),
  hover_(false)
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



bool StateMainMenue::handleGuiEvents( const irr::SEvent& event )
{
    bool result = false;
    gui::IGUIElement* caller_ = event.GUIEvent.Caller;
    gui::EGUI_ELEMENT_TYPE callerType_ = caller_->getType();
    callerID_ = caller_->getID();
    switch ( event.GUIEvent.EventType )
    {
        case gui::EGET_ELEMENT_HOVERED:
            //printf("hover_. Caller: %i\n", this->callerID_);
            if ( callerType_ == gui::EGUIET_BUTTON )
            {
                ((gui::IGUIButton*)caller_)->setImage(
                        menueScreenImageCatalogue_,
                        core::recti( 661, 115, 976, 204 )
                );
                Ton::getInstance().playGUISound( Ton::SND_GUI_HOVER );
            }
            hover_ = true;
            break;
        case gui::EGET_ELEMENT_LEFT:
            //printf("no more hover_. Caller: %i\n", this->callerID_);
            if ( callerType_ == gui::EGUIET_BUTTON )
            {
                ((gui::IGUIButton*)caller_)->setImage(
                        menueScreenImageCatalogue_,
                        core::recti( 654, 22, 966, 110 )
                );
            }
            hover_ = false;
            break;
        case gui::EGET_BUTTON_CLICKED:
            switch ( 1 )
            {
                case 1:
                    result = mainMenueButtonHandler();
                    break;
//                case MENUE_NEUER_SPIELER:
//                    result = newPlayerMenueButtonHandler();
//                    break;
//                case MENUE_HAUPTMENUE_LADEN:
//                    result = loadMenueButtonHandler();
//                    break;
//                case MENUE_HAUPTMENUE_EINSTELLUNGEN:
//                    result = prefsMenueButtonHandler();
//                    break;
//                case MENUE_MITWIRKENDE:
//                    result = aboutMenueButtonHandler();
//                    break;
                default:
                    break;
            }
            break;
        case gui::EGET_ELEMENT_FOCUSED:
            //printf("InFocus, Caller: %i\n", this->callerID_);
            break;
        case gui::EGET_ELEMENT_FOCUS_LOST:
            //printf("OutOfFocus, Caller: %i\n", this->callerID_);
            break;
        default:
            Logfile::getInstance().writeLine( Logfile::DEBUG,
                    "unbehandelter GUI-Event, Caller: %i\n", callerID_);
            break;
    }
    return result;
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
    driver_->makeColorKeyTexture( menueScreenImageCatalogue_, COL_MAGICPINK );
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
            ID_HM_BGIMAGE  // id
    );
    menueBgImage->setImage( mainMenueTexture_ );

    core::dimension2du buttonSize = core::dimension2du( 313, 88 );
    gui::IGUIButton* newButton = guienv->addButton(
            core::recti( core::position2di( 85, 63 ), buttonSize),
            menueBgImage,
            ID_HM_NEWBUTTON,
            L"Neues Spiel"
    );
    changeStyleOfButton( newButton );

    gui::IGUIButton* resumeButton = guienv->addButton(
            core::recti( core::position2di( 85, 134 ), buttonSize ),
            menueBgImage, ID_HM_RESUMEBUTTON, L"Fortsetzen"
    );
    changeStyleOfButton( resumeButton );

    gui::IGUIButton* loadButton = guienv->addButton(
            core::recti( core::position2di( 85, 207 ), buttonSize ),
            menueBgImage, ID_HM_LOADBUTTON, L"Laden"
    );
    changeStyleOfButton( loadButton );

    gui::IGUIButton* prefsButton = guienv->addButton(
            core::recti( core::position2di( 85, 288 ), buttonSize ),
            menueBgImage, ID_HM_PREFSBUTTON, L"Einstellungen"
    );
    changeStyleOfButton( prefsButton );

    gui::IGUIButton* aboutButton = guienv->addButton(
            core::recti( core::position2di( 85, 356 ), buttonSize ),
            menueBgImage, ID_HM_ABOUTBUTTON, L"Mitwirkende"
    );
    changeStyleOfButton( aboutButton );

    gui::IGUIButton* exitButton = guienv->addButton(
            core::recti( core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_HM_EXITBUTTON, L"Beenden"
    );
    changeStyleOfButton( exitButton );
}



void StateMainMenue::changeStyleOfButton( gui::IGUIButton* button)
{
    button->setImage(
            menueScreenImageCatalogue_,
            core::recti( 654, 22, 966, 110 )
    );
    button->setPressedImage(
            menueScreenImageCatalogue_,
            core::recti( 661, 115, 976, 204 )
    );
    button->setIsPushButton( false );
    button->setDrawBorder( false );
    button->setUseAlphaChannel( true );
    button->setVisible( true );
}



bool StateMainMenue::mainMenueButtonHandler()
{
    switch ( callerID_ )
    {
        case ID_HM_NEWBUTTON:
            //transitTo( MENUE_NEUER_SPIELER );
            break;
        case ID_HM_RESUMEBUTTON:
            //transitTo( MENUE_SPIEL_LAEUFT );
            break;
        case ID_HM_LOADBUTTON:
            //transitTo( MENUE_HAUPTMENUE_LADEN );
            break;
        case ID_HM_PREFSBUTTON:
            //transitTo( MENUE_HAUPTMENUE_EINSTELLUNGEN );
            break;
        case ID_HM_ABOUTBUTTON:
            //transitTo( MENUE_MITWIRKENDE );
            break;
        case ID_HM_EXITBUTTON:
            device_->closeDevice();
            break;
        default:
            Logfile::getInstance().writeLine( Logfile::DEBUG,
                    "unbekannter Knopf geklickt, Caller: %i\n", callerID_ );
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return false;
}
