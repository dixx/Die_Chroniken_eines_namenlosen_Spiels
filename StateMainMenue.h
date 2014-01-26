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
      \param -
      \return `true` wenn GUI-Event behandelt wurde, ansonsten `false`
    */
    bool handleGuiEvents();

private:

    IrrlichtDevice* device_;

    StateMainMenue( const StateMainMenue& );
    StateMainMenue& operator=( const StateMainMenue& );

    void transitTo( internalState state );

};
// Ende class StateMainMenue

#endif
// Ende Header-Datei StateMainMenue
