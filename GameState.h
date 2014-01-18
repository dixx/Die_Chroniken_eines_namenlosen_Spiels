/*! \file GameState.h
  \brief Klasse stellt Interface fuer Spiel-Stati bereit.
*/

#ifndef _GAMESTATE_H_EADER
#define _GAMESTATE_H_EADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class GameState GameState.h "GameState.h"
  \brief Interface für Spiel-Stati.
  \attention Klasse hat pure virtual Methoden!
  \note Instanzierung: niemals. Nur zum Erben gedacht.
*/
class GameState
{

public:

    /*! \brief Konstruktor.
      \param -
      \return -
    */
    GameState() {};

	// Destruktor
	virtual ~GameState() {};

    /*!
     *
     */
    //virtual void start() = 0;

    /*!
     *
     */
    //virtual void end() = 0;

    /*!
     *
     */
    //virtual void pause() = 0;

    /*!
     *
     */
    //virtual void resume() = 0;

    /*! \brief Aktualisiert den Status.
      \attention Methode ist pure virtual!
      \param frameDeltaTime (\a const \a f32) Dauer des letzten Frames in
             Sekunden
      \return -
    */
    virtual void update( const f32 frameDeltaTime ) = 0;

    /*! \brief Zeichnet den Status auf den Bildschirm.
      \attention Methode ist pure virtual!
      \param -
      \return -
    */
    virtual void draw() = 0;

    /*! \brief Erweiterung für Eventreceiver, behandelt GUI-Events des Status.
      \attention Methode ist pure virtual!
      \param -
      \return `true` wenn GUI-Event behandelt wurde, ansonsten `false`
    */
	virtual bool handleGuiEvents() = 0;

private:

    GameState( const GameState& );
    GameState& operator=( const GameState& );

};
// Ende class GameState

#endif
// Ende Header-Datei GameState
