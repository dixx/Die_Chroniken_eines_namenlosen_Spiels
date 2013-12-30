/*! \file GameStateManager.h
  \brief Klasse (Singleton) stellt Schnittstelle für Zugriff auf die
         verschiedenen Stati des Spiels bereit.
*/

#ifndef _GAMESTATEMANAGER_HEADER
#define _GAMESTATEMANAGER_HEADER

// Linken der IRRLICHT-DLL, nur in VisualStudio nötig
//#ifdef _IRR_WINDOWS_
//    #pragma comment(lib, "Irrlicht.lib")
//#endif

#include <irrlicht.h>
#include "GameState.h"

using namespace irr;
// Die innenliegenden Namespaces "core", "video" usw. werden im Folgenden
// immer explizit angegeben, um den Überblick zu behalten.

/*! \class GameStateManager GameStateManager.h "GameStateManager.h"
  \brief  Schnittstelle für Zugriff auf die verschiedenen Stati des Spiels
  \attention Klasse ist `Singleton`.
  \note Instanzierung: `GameStateManager& myGameStateManager =
        GameStateManager::getInstance();`
        \n Oder: `GameStateManager::getInstance();`
        \n Benutzen: `myGameStateManager.update();`
        \n Oder: `GameStateManager::getInstance().draw();`
*/
class GameStateManager
{

public:

    /*! \brief Die verschiedenen Stati, die das Spiel annehmen kann
    */
	enum State {
	    STARTUP = 0,  //!< Initialisieren des Spiels
	    MAIN_MENU,    //!< Das Hauptmenü und dessen Untermenüs
        GAME,         //!< Das Spiel selbst
        SHUTDOWN,     //!< Herunterfahren des Spiels

        STATES_COUNT  //!< Anzahl verfügbarer Spiel-Stati
	};

    /*! \brief Ersatz für den Konstruktor.

      Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
      \param device (\a IrrlichtDevice*) Zeiger auf das Entchen
      \return Referenz auf die einzige Instanz dieser Klasse
	*/
    static GameStateManager& getInstance( IrrlichtDevice* device = 0 );

    /*! \brief Liefert den momentan aktiven Status zurück.
      \param -
      \return \a GameState* Zeiger auf den momentan aktiven Spiel-State
    */
	GameState* getActiveState();

    /*! \brief Setzt einen neuen Spiel-State als 'aktiv'.
      \param state (\a State) zu aktivierender Spiel-State
      \return -
    */
	void setActiveState( State state );

private:

    IrrlichtDevice* device_;
	core::array<GameState*> states_;
	GameState* currentState_;

    GameStateManager( IrrlichtDevice* device );
    GameStateManager( const GameStateManager& );
    GameStateManager& operator=( const GameStateManager& );
    ~GameStateManager();

};
// Ende class GameStateManager

#endif
// Ende Header-Datei GameStateManager
