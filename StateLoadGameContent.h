/*! \file StateLoadGameContent.h
 *  \brief Klasse stellt Schnittstelle für das Laden von spielrelevanten Daten bereit.
 */

#ifndef _STATELOADGAMECONTENT_HEADER
#define _STATELOADGAMECONTENT_HEADER

#include <irrlicht.h>
#include "TransitionGameState.h"

using namespace irr;

/*! \class StateLoadGameContent StateLoadGameContent.h "StateLoadGameContent.h"
 *  \brief Schnittstelle für das Laden von spielrelevanten Daten.
 *  \note Instanzierung: `StateLoadGameContent* myStateLoadGameContent = new StateLoadGameContent();`
 * 		  \n Benutzen: `myStateLoadGameContent->update(...);`
 */
class StateLoadGameContent : public TransitionGameState
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return Zeiger auf das instanzierte Klassenobjekt
     */
    StateLoadGameContent( IrrlichtDevice* device );

	/*! \brief Destruktor
     */
	~StateLoadGameContent();

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
    core::stringc levelName_;
    u32 moduleCounter_;
    gui::IGUIImage* loadingScreenImageFrame_;
    gui::IGUIStaticText* loadingText_;

    StateLoadGameContent( const StateLoadGameContent& );
    StateLoadGameContent& operator=( const StateLoadGameContent& );

    void transitTo( internalState state );
    void createLoadingScreenImage();
    void createLoadingScreenText();

};

#endif
