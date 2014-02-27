/*! \file StatePlayTheGame.h
  \brief Klasse stellt Schnittstelle für das eigentliche Spiel bereit.
*/

#ifndef _STATEPLAYTHEGAME_HEADER
#define _STATEPLAYTHEGAME_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "GameState.h"

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class StatePlayTheGame StatePlayTheGame.h "StatePlayTheGame.h"
  \brief Schnittstelle für das Spiel.
  \note Instanzierung: `StatePlayTheGame* myStatePLayTheGame =
        new StatePlayTheGame();`
		\n Benutzen: `myStatePLayTheGame->update(...);`
*/
class StatePlayTheGame : public GameState
{

public:

    /*! \brief Konstruktor.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return Zeiger auf das instanzierte Klassenobjekt
    */
    StatePlayTheGame( IrrlichtDevice* device );

	/*! \brief Destruktor
    */
	~StatePlayTheGame();

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

    IrrlichtDevice* device_;

    StatePlayTheGame( const StatePlayTheGame& );
    StatePlayTheGame& operator=( const StatePlayTheGame& );

    void transitTo( internalState state );
    void checkInputForGame( f32 frameDeltaTime );
    void checkCameraSpecificInput( f32 frameDeltaTime );
    void checkGameSpecificInput();

};
// Ende class StatePlayTheGame

#endif
// Ende Header-Datei StatePlayTheGame
