/*! \file StateStartup.h
  \brief Klasse stellt Startup-Routinen für das Spiel bereit.

  Fast alle Singletons werden hier initialisiert (in der richtigen Reihenfolge).
*/

#ifndef _STATESTARTUP_HEADER
#define _STATESTARTUP_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "GameState.h"

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class StateStartup StateStartup.h "StateStartup.h"
  \brief Startup-Routinen für das Spiel.

  Fast alle Singletons werden hier initialisiert (in der richtigen Reihenfolge).
  \note Instanzierung: `StateStartup* myStateStartup = new StateStartup();`
        \n Benutzen: `myStateStartup->update();`
*/
class StateStartup : public GameState
{

public:

    /*! \brief Konstruktor.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return -
    */
    StateStartup( IrrlichtDevice* device );

    // Destruktor
    ~StateStartup();

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

    StateStartup( const StateStartup& );
    StateStartup& operator=( const StateStartup& );

};
// Ende class StateStartup

#endif
// Ende Header-Datei StateStartup
