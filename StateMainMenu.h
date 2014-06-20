/*! \file StateMainMenu.h
 *  \brief Klasse stellt Schnittstelle für dem Spiel vorgelagerte Menüs bereit.
 */

#ifndef _STATEMAINMENU_HEADER
#define _STATEMAINMENU_HEADER

#include <irrlicht.h>
#include "GameState.h"

using namespace irr;

/*! \class StateMainMenu StateMainMenu.h "StateMainMenu.h"
 *  \brief Schnittstelle für dem Spiel vorgelagerte Menüs.
 *  \note Instanzierung: `StateMainMenu* myStateMainMenu = new StateMainMenu();`
 *        \n Benutzen: `myStateMainMenu->update();`
 */
class StateMainMenu : public GameState
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return -
     */
    StateMainMenu( IrrlichtDevice* device );

    /*! \brief Destruktor.
     */
    ~StateMainMenu();

    /*! \brief Aktualisiert die Startup-Phase des Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void start( const f32 frameDeltaTime );

    /*! \brief Aktualisiert die Shutdown-Phase Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void shutdown( const f32 frameDeltaTime );

    /*! \brief Aktualisiert den Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void update( const f32 frameDeltaTime );

    /*! \brief Zeichnet den Status auf den Bildschirm.
     *  \param -
     *  \return -
     */
    void draw();

    /*! \brief Erweiterung für Eventreceiver, behandelt GUI-Events des Status.
     *  \param event (\a irr::SEvent&) Event-Referenz
     *  \return `true` wenn GUI-Event behandelt wurde, ansonsten `false`
     */
    bool handleGuiEvents( const irr::SEvent& event );

private:

    enum MENU
    {
        NONE  = 0,
        MAIN  = 0x100000,
        NEW   = 0x200000,
        LOAD  = 0x300000,
        PREFS = 0x400000,
        ABOUT = 0x800000
    };

    enum GUI_ITEM
    {
        ID_ROOT = 1,
        ID_MAIN_BGIMAGE       = MAIN,   //!< Hauptmenü Hintergrundbild
        ID_MAIN_NEWBUTTON,              //!< Neu-Button im Hauptmenü
        ID_MAIN_RESUMEBUTTON,           //!< Fortsetzen-Button im Hauptmenü
        ID_MAIN_LOADBUTTON,             //!< Laden-Button im Hauptmenü
        ID_MAIN_PREFSBUTTON,            //!< Einstellungen-Button im Hauptmenü
        ID_MAIN_ABOUTBUTTON,            //!< Mitwirkende-Button im Hauptmenü
        ID_MAIN_EXITBUTTON,             //!< Exit-Button im Hauptmenü
        ID_NEW_BGIMAGE        = NEW,    //!< NewPlayerMenü Hintergrundbild
        ID_NEW_EXITBUTTON,              //!< Exit-Button im NewPlayerMenü
        ID_LOAD_BGIMAGE       = LOAD,   //!< LoadMenü Hintergrundbild
        ID_LOAD_EXITBUTTON,             //!< Exit-Button im LoadMenü
        ID_PREFS_BGIMAGE      = PREFS,  //!< PrefsMenü Hintergrundbild
        ID_PREFS_EXITBUTTON,            //!< Exit-Button im PrefsMenü
        ID_ABOUT_BGIMAGE      = ABOUT,  //!< AboutMenü Hintergrundbild
        ID_ABOUT_EXITBUTTON             //!< Exit-Button im AboutMenü
    };

#ifdef _DEBUG_MODE
    IrrlichtDevice* device_;
#endif
    video::IVideoDriver* driver_;
    gui::IGUIEnvironment* guienv_;
    video::ITexture* menuScreenImageCatalogue_;
    video::ITexture* mainMenuTexture_;
    video::SColor mainMenuBgColor_;
    bool hover_;
    MENU currentMenu_;
    gui::IGUIElement* menuRoot_;

    StateMainMenu( const StateMainMenu& );
    StateMainMenu& operator=( const StateMainMenu& );

    void transitTo( internalState state );
    void loadTextures();
    void extractImagesFromCatalogue();
    void createMainMenu();
    bool mainMenuButtonHandler( s32 callerId );
    void createNewPlayerMenu();
    bool newPlayerMenuButtonHandler( s32 callerId );
    void createLoadGameMenu();
    bool loadGameMenuButtonHandler( s32 callerId );
    void createPreferencesMenu();
    bool preferencesMenuButtonHandler( s32 callerId );
    void createAboutMenu();
    bool aboutMenuButtonHandler( s32 callerId );
    inline void changeStyleOfButton( gui::IGUIButton* button );
    inline void normalizeButton( gui::IGUIButton* button );
    inline void focusButton( gui::IGUIButton* button );
    void unknownCaller( s32 callerId );
    void switchToMenu( MENU menu );
    inline void displayMenu( MENU menu );
    inline void hideMenu( MENU menu );
    void updateWithChildren( gui::IGUIElement* element, bool enable );
    void removeChildren( gui::IGUIElement* element );

};

#endif
