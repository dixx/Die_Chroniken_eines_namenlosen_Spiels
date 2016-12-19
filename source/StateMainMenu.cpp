#include "StateMainMenu.h"
#include "Configuration.h"
#include "Constants.h"
#include "Eventreceiver.h"
#include "GameStateManager.h"
#include "GenericHelperMethods.h"
#include "Mauspfeil.h"
#include "Logfile.h"
#include "SaveGames.h"
#include "Ton.h"
#ifdef _DEBUG_MODE
#include "DebugStatistics.h"
#include "Debugwindow.h"
#include "Collision.h"
#include "ObjectManager.h"
#endif



StateMainMenu::StateMainMenu( irr::IrrlichtDevice* device )
: GameState(),
#ifdef _DEBUG_MODE
  device_(device),
#endif
  driver_(0),
  guienv_(0),
  menuScreenImageCatalogue_(0),
  mainMenuTexture_(0),
  mainMenuBgColor_(irr::video::SColor( 255, 248, 245, 240 )),
  hover_(false),
  currentMenu_(NONE)
{
    if ( device == 0 )
        Logfile::getInstance().emergencyExit( "Entchen in [StateMainMenu] nicht mehr gefunden! Abbruch." );
    driver_ = device->getVideoDriver();
    guienv_ = device->getGUIEnvironment();
    menuRoot_ = guienv_->addModalScreen( guienv_->getRootGUIElement() );
    device->setWindowCaption( L"Die Chroniken eines namenlosen Spiels" );
    loadTextures();
    extractImagesFromCatalogue();
    createMainMenu();
    createNewPlayerMenu();
    createLoadGameMenu();
    createPreferencesMenu();
    createAboutMenu();
    switchToMenu( MAIN );
    transitTo( STARTING );
}



StateMainMenu::~StateMainMenu()
{
    // Niemals droppen, wenn Objekt nicht durch "create" erzeugt wurde!
    //guienv_->clear(); // NEVER DO THAT UNTIL YOU CLOSE THE PROGRAM!
    removeChildren( menuRoot_->getElementFromId( MAIN ) );
    menuRoot_->getElementFromId( MAIN )->remove();
    removeChildren( menuRoot_->getElementFromId( NEW ) );
    menuRoot_->getElementFromId( NEW )->remove();
    removeChildren( menuRoot_->getElementFromId( LOAD ) );
    menuRoot_->getElementFromId( LOAD )->remove();
    removeChildren( menuRoot_->getElementFromId( PREFS ) );
    menuRoot_->getElementFromId( PREFS )->remove();
    removeChildren( menuRoot_->getElementFromId( ABOUT ) );
    menuRoot_->getElementFromId( ABOUT )->remove();
    // menuRoot_ removes itself after all children are gone
    driver_->removeTexture( mainMenuTexture_ );
}



void StateMainMenu::start( irr::f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on startup
    transitTo( RUNNING );
}



void StateMainMenu::update( irr::f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics
    if ( Eventreceiver::getInstance().hasKeyJustBeenReleased( irr::KEY_ESCAPE ) )
    {
        GameStateManager::getInstance().requestNewState( GameStateManager::SHUTDOWN );
        transitTo( STOPPING );
    }
#ifdef _DEBUG_MODE
    if ( Eventreceiver::getInstance().hasKeyJustBeenReleased( irr::KEY_F1 ) )
        Debugwindow::getInstance().toggle();
    if ( Eventreceiver::getInstance().hasKeyJustBeenReleased( irr::KEY_F2 ) )
    {
        DebugStatistics( device_ ).writeStatisticsToLogfile();
    }
    Debugwindow::getInstance().addLine( "StateMainMenu::update1", L"loaded selectors: ", Collision::getInstance().loadedSelectors() );
    Debugwindow::getInstance().addLine( "StateMainMenu::update2", L"loaded nodes: ", ObjectManager::getInstance().loadedNodes() );
#endif
}



void StateMainMenu::shutdown( irr::f32 frameDeltaTime )
{
    (void)frameDeltaTime; // game state does no real-time graphics on shutdown
    transitTo( STOPPED );
}



void StateMainMenu::draw()
{
    driver_->beginScene( true, false, mainMenuBgColor_ );
    guienv_->drawAll();
#ifdef _DEBUG_MODE
    Debugwindow::getInstance().show();
#endif
    Mauspfeil::getInstance().draw();
    driver_->endScene();
}



bool StateMainMenu::handleGuiEvents( const irr::SEvent& event )
{
    bool result = false;
    irr::gui::IGUIElement* caller = event.GUIEvent.Caller;
    irr::gui::EGUI_ELEMENT_TYPE callerType = caller->getType();
    irr::s32 callerId = caller->getID();
    switch ( event.GUIEvent.EventType )
    {
        case irr::gui::EGET_ELEMENT_HOVERED:
            if ( callerType == irr::gui::EGUIET_BUTTON )
            {
                focusButton( static_cast<irr::gui::IGUIButton*>( caller ) );
                Ton::getInstance().playGUISound( Ton::SND_GUI_HOVER );
            }
            hover_ = true;
            break;
        case irr::gui::EGET_ELEMENT_LEFT:
            if ( callerType == irr::gui::EGUIET_BUTTON )
                normalizeButton( static_cast<irr::gui::IGUIButton*>( caller ) );
            hover_ = false;
            break;
        case irr::gui::EGET_BUTTON_CLICKED:
            switch ( currentMenu_ )
            {
                case MAIN:
                    result = mainMenuButtonHandler( callerId );
                    break;
                case NEW:
                    result = newPlayerMenuButtonHandler( callerId );
                    break;
                case LOAD:
                    result = loadGameMenuButtonHandler( callerId );
                    break;
                case PREFS:
                    result = preferencesMenuButtonHandler( callerId );
                    break;
                case ABOUT:
                    result = aboutMenuButtonHandler( callerId );
                    break;
                default:
                    break;
            }
            break;
        case irr::gui::EGET_ELEMENT_FOCUSED:
            //printf("InFocus, Caller: %i\n", this->callerID_);
            break;
        case irr::gui::EGET_ELEMENT_FOCUS_LOST:
            //printf("OutOfFocus, Caller: %i\n", this->callerID_);
            break;
        default:
            Logfile::getInstance().writeLine( Logfile::DEBUG, "unbehandelter GUI-Event, Caller: %i\n", callerId );
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
            Eventreceiver::getInstance().setEventReactionActive( true, true, true );
            Mauspfeil::getInstance().setCurrentArrow( Mauspfeil::MAUSPFEIL_SELECT );
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
    driver_->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );
    helper.validateFileExistence( "GFX/menues1.bmp" );
    menuScreenImageCatalogue_ = driver_->getTexture( "GFX/menues1.bmp" );
    driver_->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, true );
}



void StateMainMenu::extractImagesFromCatalogue()
{
    driver_->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, false );
    driver_->disableFeature( irr::video::EVDF_BILINEAR_FILTER, true );
    irr::video::IImage* wholeImage = driver_->createImageFromFile( menuScreenImageCatalogue_->getName() );
    if ( !wholeImage )
        Logfile::getInstance().emergencyExit( "Bild nicht geladen!" );
    driver_->makeColorKeyTexture( menuScreenImageCatalogue_, COL_MAGICPINK );
    // Ausschneiden des mainMenue-Hintergrundbildes als eigene Textur
    irr::core::dimension2du menueTextureSize = irr::core::dimension2du( 436, 555 );
    irr::video::IImage* partialImage = driver_->createImage( wholeImage->getColorFormat(), menueTextureSize );
    wholeImage->copyTo(
            partialImage,
            irr::core::position2di( 0, 0 ),
            irr::core::recti( irr::core::position2di( 588, 212 ), menueTextureSize )
    );
    mainMenuTexture_ = driver_->addTexture( "GFX/mainMenueTexture.virtual", partialImage );
    partialImage->drop();
    driver_->makeColorKeyTexture( mainMenuTexture_, COL_MAGICPINK );
    wholeImage->drop();
    driver_->disableFeature( irr::video::EVDF_BILINEAR_FILTER, false );
    driver_->setTextureCreationFlag( irr::video::ETCF_CREATE_MIP_MAPS, true );
}



void StateMainMenu::createMainMenu()
{
    irr::core::dimension2du textureSize = mainMenuTexture_->getSize();
    irr::core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    irr::core::position2di imagePosition = irr::core::position2di(
            static_cast<irr::s32>( screenSize.Width - 20 - textureSize.Width ),
            static_cast<irr::s32>( screenSize.Height - 20 - textureSize.Height )
    );
    irr::core::dimension2du buttonSize = irr::core::dimension2du( 313, 88 );
    irr::gui::IGUIImage* menueBgImage = guienv_->addImage(
            irr::core::recti( imagePosition, textureSize ),
            menuRoot_, ID_MAIN_BGIMAGE, L"Hauptmenü"
    );
    menueBgImage->setImage( mainMenuTexture_ );
    irr::gui::IGUIButton* newButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 63 ), buttonSize ),
            menueBgImage, ID_MAIN_NEWBUTTON, L"Neues Spiel"
    );
    changeStyleOfButton( newButton );
    irr::gui::IGUIButton* resumeButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 134 ), buttonSize ),
            menueBgImage, ID_MAIN_RESUMEBUTTON, L"Fortsetzen"
    );
    changeStyleOfButton( resumeButton );
    if ( SaveGames( device_ ).findNewest().empty() )
        menueBgImage->removeChild( resumeButton );
    irr::gui::IGUIButton* loadButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 207 ), buttonSize ),
            menueBgImage, ID_MAIN_LOADBUTTON, L"Laden"
    );
    changeStyleOfButton( loadButton );
    irr::gui::IGUIButton* prefsButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 288 ), buttonSize ),
            menueBgImage, ID_MAIN_PREFSBUTTON, L"Einstellungen"
    );
    changeStyleOfButton( prefsButton );
    irr::gui::IGUIButton* aboutButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 356 ), buttonSize ),
            menueBgImage, ID_MAIN_ABOUTBUTTON, L"Mitwirkende"
    );
    changeStyleOfButton( aboutButton );
    irr::gui::IGUIButton* exitButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_MAIN_EXITBUTTON, L"Beenden"
    );
    changeStyleOfButton( exitButton );
    hideMenu( MAIN );
}



bool StateMainMenu::mainMenuButtonHandler( irr::s32 callerId )
{
    bool result = true;
    switch ( callerId )
    {
        case ID_MAIN_NEWBUTTON:
            switchToMenu( NEW );
            break;
        case ID_MAIN_RESUMEBUTTON:
            GameStateManager::getInstance().requestNewState( GameStateManager::LOAD );
            transitTo( STOPPING );
            break;
        case ID_MAIN_LOADBUTTON:
            switchToMenu( LOAD );
            break;
        case ID_MAIN_PREFSBUTTON:
            switchToMenu( PREFS );
            break;
        case ID_MAIN_ABOUTBUTTON:
            switchToMenu( ABOUT );
            break;
        case ID_MAIN_EXITBUTTON:
            GameStateManager::getInstance().requestNewState( GameStateManager::SHUTDOWN );
            transitTo( STOPPING );
            break;
        default:
            unknownCaller( callerId );
            result = false;
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return result;
}



void StateMainMenu::createNewPlayerMenu()
{
    irr::core::dimension2du textureSize = mainMenuTexture_->getSize();
    irr::core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    irr::core::position2di imagePosition = irr::core::position2di(
            static_cast<irr::s32>( screenSize.Width - 20 - textureSize.Width ),
            static_cast<irr::s32>( screenSize.Height - 20 - textureSize.Height )
    );
    irr::core::dimension2du buttonSize = irr::core::dimension2du( 313, 88 );
    irr::gui::IGUIImage* menueBgImage = guienv_->addImage(
            irr::core::recti( imagePosition, textureSize ),
            menuRoot_, ID_NEW_BGIMAGE, L"Neuer Spieler"
    );
    menueBgImage->setImage( mainMenuTexture_ );
    irr::gui::IGUIButton* exitButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_NEW_EXITBUTTON, L"Zurück"
    );
    changeStyleOfButton( exitButton );
    hideMenu( NEW );
}



bool StateMainMenu::newPlayerMenuButtonHandler( irr::s32 callerId )
{
    bool result = true;
    switch ( callerId )
    {
        case ID_NEW_EXITBUTTON:
        {
            SaveGames( device_ ).save( "SAVEGAMES/test.sav" );
            switchToMenu( MAIN );
            break;
        }
        default:
            unknownCaller( callerId );
            result = false;
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return result;
}



void StateMainMenu::createLoadGameMenu()
{
    irr::core::dimension2du textureSize = mainMenuTexture_->getSize();
    irr::core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    irr::core::position2di imagePosition = irr::core::position2di(
            static_cast<irr::s32>( screenSize.Width - 20 - textureSize.Width ),
            static_cast<irr::s32>( screenSize.Height - 20 - textureSize.Height )
    );
    irr::core::dimension2du buttonSize = irr::core::dimension2du( 313, 88 );
    irr::gui::IGUIImage* menueBgImage = guienv_->addImage(
            irr::core::recti( imagePosition, textureSize ),
            menuRoot_, ID_LOAD_BGIMAGE, L"Spiel laden"
    );
    menueBgImage->setImage( mainMenuTexture_ );
    irr::gui::IGUIButton* exitButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_LOAD_EXITBUTTON, L"Zurück"
    );
    changeStyleOfButton( exitButton );
    hideMenu( LOAD );
}



bool StateMainMenu::loadGameMenuButtonHandler( irr::s32 callerId )
{
    bool result = true;
    switch ( callerId )
    {
        case ID_LOAD_EXITBUTTON:
            switchToMenu( MAIN );
            break;
        default:
            unknownCaller( callerId );
            result = false;
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return result;
}



void StateMainMenu::createPreferencesMenu()
{
    irr::core::dimension2du textureSize = mainMenuTexture_->getSize();
    irr::core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    irr::core::position2di imagePosition = irr::core::position2di(
            static_cast<irr::s32>( screenSize.Width - 20 - textureSize.Width ),
            static_cast<irr::s32>( screenSize.Height - 20 - textureSize.Height )
    );
    irr::core::dimension2du buttonSize = irr::core::dimension2du( 313, 88 );
    irr::gui::IGUIImage* menueBgImage = guienv_->addImage(
            irr::core::recti( imagePosition, textureSize ),
            menuRoot_, ID_PREFS_BGIMAGE, L"Einstellungen"
    );
    menueBgImage->setImage( mainMenuTexture_ );
    irr::gui::IGUIButton* exitButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_PREFS_EXITBUTTON, L"Zurück"
    );
    changeStyleOfButton( exitButton );
    hideMenu( PREFS );
}



bool StateMainMenu::preferencesMenuButtonHandler( irr::s32 callerId )
{
    bool result = true;
    switch ( callerId )
    {
        case ID_PREFS_EXITBUTTON:
            switchToMenu( MAIN );
            break;
        default:
            unknownCaller( callerId );
            result = false;
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return result;
}



void StateMainMenu::createAboutMenu()
{
    irr::core::dimension2du textureSize = mainMenuTexture_->getSize();
    irr::core::dimension2du screenSize = Configuration::getInstance().getScreenSize();
    irr::core::position2di imagePosition = irr::core::position2di(
            static_cast<irr::s32>( screenSize.Width - 20 - textureSize.Width ),
            static_cast<irr::s32>( screenSize.Height - 20 - textureSize.Height )
    );
    irr::core::dimension2du buttonSize = irr::core::dimension2du( 313, 88 );
    irr::gui::IGUIImage* menueBgImage = guienv_->addImage(
            irr::core::recti( imagePosition, textureSize ),
            menuRoot_, ID_ABOUT_BGIMAGE, L"Über..."
    );
    menueBgImage->setImage( mainMenuTexture_ );
    irr::gui::IGUIButton* exitButton = guienv_->addButton(
            irr::core::recti( irr::core::position2di( 85, 416 ), buttonSize ),
            menueBgImage, ID_ABOUT_EXITBUTTON, L"Zurück"
    );
    changeStyleOfButton( exitButton );
    hideMenu( ABOUT );
}



bool StateMainMenu::aboutMenuButtonHandler( irr::s32 callerId )
{
    bool result = true;
    switch ( callerId )
    {
        case ID_ABOUT_EXITBUTTON:
            switchToMenu( MAIN );
            break;
        default:
            unknownCaller( callerId );
            result = false;
            break;
    }
    Ton::getInstance().playGUISound( Ton::SND_GUI_CLICKBUTTON );
    return result;
}



void StateMainMenu::changeStyleOfButton( irr::gui::IGUIButton* button)
{
    normalizeButton( button );
    button->setPressedImage(  menuScreenImageCatalogue_, irr::core::recti( 661, 115, 976, 204 ) );
    button->setIsPushButton( false );
    button->setDrawBorder( false );
    button->setUseAlphaChannel( true );
}



void StateMainMenu::normalizeButton( irr::gui::IGUIButton* button )
{
    button->setImage( menuScreenImageCatalogue_, irr::core::recti( 654, 22, 966, 110 ) );
}



void StateMainMenu::focusButton( irr::gui::IGUIButton* button )
{
    button->setImage( menuScreenImageCatalogue_, irr::core::recti( 661, 115, 976, 204 ) );
}



void StateMainMenu::unknownCaller( irr::s32 callerId )
{
    Logfile::getInstance().writeLine( Logfile::DEBUG, "unbekannter Knopf geklickt, CallerID: ", callerId );
}



void StateMainMenu::switchToMenu( MENU menu )
{
    if ( menu )
    {
        Eventreceiver::getInstance().setEventReactionActive( false, false, false );
        hideMenu( currentMenu_ );
        currentMenu_ = menu;
        displayMenu( currentMenu_ );
        Eventreceiver::getInstance().setEventReactionActive( true, true, true );
    }
}



void StateMainMenu::displayMenu( MENU menu )
{
    updateWithChildren( menuRoot_->getElementFromId( menu ), true );
}



void StateMainMenu::hideMenu( MENU menu )
{
    updateWithChildren( menuRoot_->getElementFromId( menu ), false );
}



void StateMainMenu::updateWithChildren( irr::gui::IGUIElement* element, bool enable )
{
    if ( !element )
        return;
    element->setVisible( enable );
    element->setEnabled( enable );
    irr::core::list<irr::gui::IGUIElement*> children = element->getChildren();
    if ( children.empty() )
        return;
    irr::core::list<irr::gui::IGUIElement*>::Iterator it = children.begin();
    for ( ; it != children.end(); ++it )
        updateWithChildren( (*it), enable );
}



void StateMainMenu::removeChildren( irr::gui::IGUIElement* element )
{
    if ( !element )
        return;
    const irr::core::list<irr::gui::IGUIElement*>& children = element->getChildren();
    if ( children.empty() )
        return;
    while ( true )
    {
        removeChildren( *(children.getLast()) );
        element->removeChild( *(children.getLast()) );
        if ( children.empty() )
            break;
    }
}
