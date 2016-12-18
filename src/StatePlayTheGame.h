/*! \file StatePlayTheGame.h
 *  \brief Klasse stellt Schnittstelle für das eigentliche Spiel bereit.
 */

#ifndef _STATEPLAYTHEGAME_HEADER
#define _STATEPLAYTHEGAME_HEADER

#include <irrlicht.h>
#include "GameState.h"

/*! \class StatePlayTheGame StatePlayTheGame.h "StatePlayTheGame.h"
 *  \brief Schnittstelle für das Spiel.
 *  \note Instanzierung: `StatePlayTheGame* myStatePLayTheGame = new StatePlayTheGame();`
 *        \n Benutzen: `myStatePLayTheGame->update(...);`
 */
class StatePlayTheGame : public GameState
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    StatePlayTheGame( irr::IrrlichtDevice* device );

	/*! \brief Destruktor
     */
	~StatePlayTheGame();

    /*! \brief Aktualisiert die Startup-Phase des Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void start( const irr::f32 frameDeltaTime );

    /*! \brief Aktualisiert die Shutdown-Phase Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void shutdown( const irr::f32 frameDeltaTime );

    /*! \brief Aktualisiert den Status.
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    void update( const irr::f32 frameDeltaTime );

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

    irr::IrrlichtDevice* device_;

    StatePlayTheGame( const StatePlayTheGame& );
    StatePlayTheGame& operator=( const StatePlayTheGame& );

    void transitTo( internalState state );
    void checkInputForGame( irr::f32 frameDeltaTime );
    void checkCameraSpecificInput( irr::f32 frameDeltaTime );
    void checkGameSpecificInput();

};

#endif
