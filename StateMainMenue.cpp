#include "StateMainMenue.h"
#include "Configuration.h"
#include "Constants.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "GenericHelperMethods.h"
#include "Mauspfeil.h"
#include "Logfile.h"
#include "Ton.h"



StateMainMenu::StateMainMenu( IrrlichtDevice* device )
: GameState(),
  driver_(0),
  guienv_(0),
  menuScreenImageCatalogue_(0),
  mainMenuTexture_(0),
  mainMenuBgColor_(video::SColor( 255, 248, 245, 240 )),
  hover_(false)
{
    if ( device == 0 )
        Logfile::getInstance().emergencyExit(
                "Entchen in [StateMainMenu] nicht mehr gefunden! Abbruch." );
    driver_ = device->getVideoDriver();
    guienv_ = device->getGUIEnvironment();
    device->setWindowCaption( L"Die Chroniken eines namenlosen Spiels" );
    loadTextures();
    extractImagesFromCatalogue();
    createMainMenu();
    transitTo( STARTING );
}



StateMainMenu::~StateMainMenu()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    guienv_->clear();
}



void StateMainMenu::start( f32 frameDeltaTime )
{
    transitTo( RUNNING );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateMainMenu::update( f32 frameDeltaTime )
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



void StateMainMenu::shutdown( f32 frameDeltaTime )
{
    transitTo( STOPPED );
#pragma GCC diagnostic ignored "-Wunused-parameter" // ==> frameDeltaTime
}
#pragma GCC diagnostic error "-Wunused-parameter"



void StateMainMenu::draw()
{
    driver_->beginScene( true, false, mainMenuBgColor_ );
    guienv_->drawAll();
    Mauspfeil::getInstance().draw();
    driver_->endScene();
}



bool StateMainMenu::handleGuiEvents( const irr::SEvent& event )
{
    bool result = false;
    gui::IGUIElement* caller = event.GUIEvent.Caller;
    gui::EGUI_ELEMENT_TYPE callerType = caller->getType();
    s32 callerId = caller->getID();
    switch ( event.GUIEvent.EventType )
    {
        case gui::EGET_ELEMENT_HOVERED:
            if ( callerType == gui::EGUIET_BUTTON )
            {
                focusButton( static_cast<gui::IGUIButton*>( caller ) );
                Ton::getInstance().playGUISound( Ton::SND_GUI_HOVER );
            }
            hover_ = true;
            break;
        case gui::EGET_ELEMENT_LEFT:
            if ( callerType == gui::EGUIET_BUTTON )
            {
                normalizeButton( static_cast<gui::IGUIButton*>( caller ) );
            }
            hover_ = false;
            break;
        case gui::EGET_BUTTON_CLICKED:
            switch ( 1 )
            {
                case 1:
                    result = mainMenuButtonHandler( callerId );
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
                    "unbehandelter GUI-Event, Caller: %i\n", callerId );
            break;
    }
    return result;
}



/* private */



void StateMainMenu::transitTo( internalState state )
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



void StateMainMenu::loadTextures()
{
    GenericHelperMethods& helper = GenericHelperMethods::getInstance();
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false );
    helper.validateFileExistence( "GFX/menues1.bmp" );
    menuScreenImageCatalogue_ = driver_->getTexture( "GFX/menues1.bmp" );
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, true );
}



void StateMainMenu::extractImagesFromCatalogue()
{
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, false );
    driver_->disableFeature( video::EVDF_BILINEAR_FILTER, true );
    video::IImage* wholeImage = driver_->createImageFromFile(
            menuScreenImageCatalogue_->getName() );
    if ( !wholeImage )
        Logfile::getInstance().emergencyExit( "Bild nicht geladen!" );
    driver_->makeColorKeyTexture( menuScreenImageCatalogue_, COL_MAGICPINK );
    // Ausschneiden des mainMenue-Hintergrundbildes als eigene Textur
    core::dimension2du menueTextureSize = core::dimension2du( 436, 555 );
    video::IImage* partialImage = driver_->createImage(
            wholeImage->getColorFormat(), menueTextureSize );
    wholeImage->copyTo(
            partialImage,
            core::position2di( 0, 0 ),
            core::recti( core::position2di( 588, 212 ), menueTextureSize )
    );
    mainMenuTexture_ = driver_->addTexture(
            "GFX/mainMenueTexture.virtual", partialImage );
    partialImage->drop();
    driver_->makeColorKeyTexture( mainMenuTexture_, COL_MAGICPINK );
    wholeImage->drop();
    driver_->disableFeature( video::EVDF_BILINEAR_FILTER, false );
    driver_->setTextureCreationFlag( video::ETCF_CREATE_MIP_MAPS, true );
}



void StateMainMenu::createMainMenu()
{
    u32 texWidth = mainMenuTexture_->getSize().Width;
    u32 texHeight = mainMenuTexture_->getSize().Height;
    core::dimension2du screen = Configuration::getInstance().getScreenSize();
    core::dimension2du buttonSize = core::dimension2du( 313, 88 );

    gui::IGUIElement* root = guienv_->getRootGUIElement();

    gui::IGUIImage* menueBgImage = guienv_->addImage(
            core::recti(
                    screen.Width - 20 - texWidth ,
                    screen.Height - 20 - texHeight,
                    screen.Width - 20,
                    screen.Height - 20
            ),  // Abmessungen auf Bildschirm
            root,  // parent
            ID_HM_BGIMAGE  // id
    );
    menueBgImage->setImage( mainMenuTexture_ );

    gui::IGUIButton* newButton = guienv_->addButton(
            core::recti( core::position2di( 85, 63 ), buttonSize ),
            menueBgImage, ID_HM_NEWBUTTON, L"Neues Spiel"
    );
    changeStyleOfButton( newButton );
    gui::IGUIButton* resumeButton = guienv_->addButton(
            core::recti( core::position2di( 85, 134 ), buttonSize ),
            menueBgImage, ID_HM_RESUMEBUTTON, L"Fortsetzen"
    );
    changeStyleOfButton( resumeButton );
    gui::IGUIButton* loadButton = guienv_->addButton(
            core::recti( core::position2di( 85, 207 ), buttonSize ),
            menueBgImage, ID_HM_LOADBUTTON, L"Laden"
    );
    changeStyleOfButton( loadButton );
    gui::IGUIButton* prefsButton = guienv_->addButton(
            core::recti( core::position2di( 85, 288 ), buttonSize ),
            menueBgImage, ID_HM_PREFSBUTTON, L"Einstellungen"
    );
    changeStyleOfButton( prefsButton );
    gui::IGUIButton* aboutButton = guienv_->addButton(
            core::recti( core::position2di( 85, 356 ), buttonSize ),
            menueBgImage, ID_HM_ABOUTBUTTON, L"Mitwirkende"
    );
    changeStyleOfButton( aboutButton );
    gui::IGUIButton* exitButton = guienv_->addButton(
            core::recti( core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_HM_EXITBUTTON, L"Beenden"
    );
    changeStyleOfButton( exitButton );
}



void StateMainMenu::changeStyleOfButton( gui::IGUIButton* button)
{
    normalizeButton( button );
    button->setPressedImage(  menuScreenImageCatalogue_,
            core::recti( 661, 115, 976, 204 ) );
    button->setIsPushButton( false );
    button->setDrawBorder( false );
    button->setUseAlphaChannel( true );
    button->setVisible( true );
}



void StateMainMenu::normalizeButton( gui::IGUIButton* button )
{
    button->setImage( menuScreenImageCatalogue_,
            core::recti( 654, 22, 966, 110 ) );
}



void StateMainMenu::focusButton( gui::IGUIButton* button )
{
    button->setImage( menuScreenImageCatalogue_,
            core::recti( 661, 115, 976, 204 ) );
}



bool StateMainMenu::mainMenuButtonHandler( s32 callerId )
{
    switch ( callerId )
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
            GameStateManager::getInstance().requestNewState(
                                GameStateManager::SHUTDOWN );
            transitTo( STOPPING );
            break;
        default:
            Logfile::getInstance().writeLine( Logfile::DEBUG,
                    "unbekannter Knopf geklickt, Caller: %i\n", callerId );
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return false;
}
