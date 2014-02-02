/*! \file StateMainMenue.h
  \brief Klasse stellt Schnittstelle für dem Spiel vorgelagerte Menüs bereit.
*/

#ifndef _STATEMAINMENUE_HEADER
#define _STATEMAINMENUE_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "GameState.h"

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class StateMainMenue StateMainMenue.h "StateMainMenue.h"
  \brief Schnittstelle für dem Spiel vorgelagerte Menüs.
  \note Instanzierung: `StateMainMenue* myStateMainMenue = new StateMainMenue();`
		\n Benutzen: `myStateMainMenue->update();`
*/
class StateMainMenue : public GameState
{

public:

    /*! \brief Konstruktor.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return -
    */
    StateMainMenue( IrrlichtDevice* device );

    // Destruktor
    ~StateMainMenue();

    /*! \brief Aktualisiert die Startup-Phase des Status.
      \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
             Sekunden
      \return -
    */
    void start( const f32 frameDeltaTime );

    /*! \brief Aktualisiert die Shutdown-Phase Status.
      \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
             Sekunden
      \return -
    */
    void shutdown( const f32 frameDeltaTime );

    /*! \brief Aktualisiert den Status.
      \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
             Sekunden
      \return -
    */
    void update( const f32 frameDeltaTime );

    /*! \brief Zeichnet den Status auf den Bildschirm.
      \param -
      \return -
    */
    void draw();

    /*! \brief Erweiterung für Eventreceiver, behandelt GUI-Events des Status.
      \param event (\a irr::SEvent&) Event-Referenz
      \return `true` wenn GUI-Event behandelt wurde, ansonsten `false`
    */
    bool handleGuiEvents( const irr::SEvent& event );

private:

    enum GUI_ITEM
    {
        ID_HM_ROOT = 0,  //!< Hauptmenue Root-Element
        ID_HM_BGIMAGE,  //!< Hauptmenue Hintergrundbild
        ID_HM_NEWBUTTON,  //!< Neu-Button im Hauptmenue
        ID_HM_RESUMEBUTTON,  //!< Fortsetzen-Button im Hauptmenue
        ID_HM_LOADBUTTON,  //!< Laden-Button im Hauptmenue
        ID_HM_PREFSBUTTON,  //!< Einstellungen-Button im Hauptmenue
        ID_HM_ABOUTBUTTON,  //!< Mitwirkende-Button im Hauptmenue
        ID_HM_EXITBUTTON,  //!< Exit-Button im Hauptmenue
        ID_NP_ROOT,  //!< NewPlayerMenue Root-Element
        ID_NP_BGIMAGE,  //!< NewPlayerMenue Hintergrundbild
        ID_NP_EXITBUTTON,  //!< Exit-Button im NewPlayerMenue
        ID_LO_ROOT,  //!< LoadMenue Root-Element
        ID_LO_BGIMAGE,  //!< LoadMenue Hintergrundbild
        ID_LO_EXITBUTTON,  //!< Exit-Button im LoadMenue
        ID_PR_ROOT,  //!< PrefsMenue Root-Element
        ID_PR_BGIMAGE,  //!< PrefsMenue Hintergrundbild
        ID_PR_EXITBUTTON,  //!< Exit-Button im PrefsMenue
        ID_AB_ROOT,  //!< AboutMenue Root-Element
        ID_AB_BGIMAGE,  //!< AboutMenue Hintergrundbild
        ID_AB_EXITBUTTON,  //!< Exit-Button im AboutMenue
        ID_COUNT  //!< Anzahl verfuegbarer Items, sicherheitsrelevant!
    };

    video::IVideoDriver* driver_;
    gui::IGUIEnvironment* guienv_;
    video::ITexture* menueScreenImageCatalogue_;
    video::ITexture* mainMenueTexture_;
    video::SColor mainMenueBgColor_;
    bool hover_;

    StateMainMenue( const StateMainMenue& );
    StateMainMenue& operator=( const StateMainMenue& );

    void transitTo( internalState state );
    void loadTextures();
    void extractImagesFromCatalogue();
    void createMainMenu();
    inline void changeStyleOfButton( gui::IGUIButton* button );
    inline void focusButton( gui::IGUIButton* button );
    inline void normalizeButton( gui::IGUIButton* button );
    bool mainMenueButtonHandler( s32 callerId );

};
// Ende class StateMainMenue

#endif
// Ende Header-Datei StateMainMenue
