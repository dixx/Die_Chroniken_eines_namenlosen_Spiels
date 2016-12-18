/*! \file GameState.h
 *  \brief Klasse stellt Interface für Spiel-Stati bereit.
 */

#ifndef _GAMESTATE_HEADER
#define _GAMESTATE_HEADER

#include <irrlicht.h>
#include "GameStateManager.h"

/*! \class GameState GameState.h "GameState.h"
 *  \brief Interface für Spiel-Stati.
 *  \attention Klasse hat pure virtual Methoden!
 *  \note Instanzierung: niemals. Nur zum Erben gedacht.
 */
class GameState
{

public:

    /*! \brief Werte, die der momentane Status des GameState annehmen kann.
     */
    enum internalState {
        INITIAL = 0,  //!< unzulässiger Status
        STARTING,     //!< GameState startet gerade
        RUNNING,      //!< GameState läuft gerade
        STOPPING,     //!< GameState beendet sich gerade
        STOPPED       //!< GameState ist beendet
    };

    /*! \brief Konstruktor.
     *  \param -
     *  \return -
     */
    GameState() : currentInternalState_(INITIAL), forceDraw_(false) {};

    /*! \brief Destruktor.
     */
	virtual ~GameState() {};

    /*! \brief Aktualisiert die Startup-Phase des Status.
     *  \attention Methode ist pure virtual!
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    virtual void start( const irr::f32 frameDeltaTime ) = 0;

    /*! \brief Aktualisiert den Status.
     *  \attention Methode ist pure virtual!
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    virtual void update( const irr::f32 frameDeltaTime ) = 0;

    /*! \brief Aktualisiert die Shutdown-Phase Status.
     *  \attention Methode ist pure virtual!
     *  \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in Sekunden
     *  \return -
     */
    virtual void shutdown( const irr::f32 frameDeltaTime ) = 0;

    /*! \brief Zeichnet den Status auf den Bildschirm.
     *  \attention Methode ist pure virtual!
     *  \param -
     *  \return -
     */
    virtual void draw() = 0;

    /*! \brief Erweiterung für Eventreceiver, behandelt GUI-Events des Status.
     *  \attention Methode ist pure virtual!
     *  \param event (\a irr::SEvent&) Event-Referenz
     *  \return `true` wenn GUI-Event behandelt wurde, ansonsten `false`
     */
	virtual bool handleGuiEvents( const irr::SEvent& event ) = 0;

    /*! \brief Liefert den momentanen Status des GameState.
     *  \param -
     *  \return \a internalState momentaner Status
     */
    internalState currentInternalState() { return currentInternalState_; };

    /*! \brief Legt fest, ob das Zeichnen für jeden Frame erzwungen werden soll.
     *  \attention Nur für zeitunkritische States!
     *  \param -
     *  \return `true` wenn Zeichnen erzwungen werden soll, ansonsten `false`
     */
    bool allFramesMustBeShown() { return forceDraw_; };

    /*!
     *
     */
    //virtual void pause() = 0;

    /*!
     *
     */
    //virtual void resume() = 0;

protected:

    internalState currentInternalState_;
    bool forceDraw_;

private:

    GameState( const GameState& );
    GameState& operator=( const GameState& );

};

#endif
