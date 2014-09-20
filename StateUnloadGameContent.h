/*! \file StateUnloadGameContent.h
 *  \brief Klasse stellt Schnittstelle für das Entaden von spielrelevanten Daten bereit.
 */

#ifndef _STATEUNLOADGAMECONTENT_HEADER
#define _STATEUNLOADGAMECONTENT_HEADER

#include <irrlicht.h>
#include "TransitionGameState.h"

using namespace irr;

/*! \class StateUnloadGameContent StateUnloadGameContent.h "StateUnloadGameContent.h"
 *  \brief Schnittstelle für das Entaden von spielrelevanten Daten.
 *  \note Instanzierung: `StateUnloadGameContent* myStateUnloadGameContent = new StateUnloadGameContent();`
 *        \n Benutzen: `myStateUnloadGameContent->update(...);`
 */
class StateUnloadGameContent : public TransitionGameState
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    StateUnloadGameContent( IrrlichtDevice* device );

	/*! \brief Destruktor
     */
	~StateUnloadGameContent();

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

    IrrlichtDevice* device_;
    u32 moduleCounter_;
    gui::IGUIImage* loadingScreenImageFrame_;
    gui::IGUIStaticText* loadingText_;

    StateUnloadGameContent( const StateUnloadGameContent& );
    StateUnloadGameContent& operator=( const StateUnloadGameContent& );

    void transitTo( internalState state );
    void createLoadingScreenImage();
    void createLoadingScreenText();

};

#endif
