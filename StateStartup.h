/*! \file StateStartup.h
 *  \brief Klasse stellt Startup-Routinen für das Spiel bereit.
 *
 *  Fast alle Singletons werden hier initialisiert (in der richtigen Reihenfolge).
 */

#ifndef _STATESTARTUP_HEADER
#define _STATESTARTUP_HEADER

#include <irrlicht.h>
#include "GameState.h"
#include "LoadingScreen.h"

using namespace irr;

/*! \class StateStartup StateStartup.h "StateStartup.h"
 *  \brief Startup-Routinen für das Spiel.
 *
 *  Fast alle Singletons werden hier initialisiert (in der richtigen Reihenfolge).
 *  \note Instanzierung: `StateStartup* myStateStartup = new StateStartup();` \n Benutzen: `myStateStartup->update();`
 */
class StateStartup : public GameState
{

public:

    /*! \brief Konstruktor.
     *  \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
     *  \return -
     */
    StateStartup( IrrlichtDevice* device );

    /*! \brief Destruktor.
     */
    ~StateStartup();

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
    u32 classCounter_;
    LoadingScreen* loadingScreen_;
    gui::IGUIInOutFader* fader_;

    StateStartup( const StateStartup& );
    StateStartup& operator=( const StateStartup& );

    void transitTo( internalState state );

};

#endif
