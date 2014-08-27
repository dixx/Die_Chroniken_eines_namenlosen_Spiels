/*! \file GameFloatControl.h
 *  \brief Klasse (Singleton) steuert den Programmablauf.
 */

#ifndef _GAMEFLOATCONTROL_HEADER
#define _GAMEFLOATCONTROL_HEADER

#include <irrlicht.h>

using namespace irr;

/*! \class GameFloatControl GameFloatControl.h "GameFloatControl.h"
 *  \brief Steuert den Programmablauf.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `GameFloatControl& myGameFloatControl = GameFloatControl::getInstance();`
 *        \n Oder: `GameFloatControl::getInstance();`
 *        \n Benutzen: `myGameFloatControl.start();`
 *        \n Oder: `GameFloatControl::getInstance().run();`
 */
class GameFloatControl
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param -
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static GameFloatControl& getInstance();

    /*! \brief Startet Logfile, liest Konfiguration, erstellt 3D-Entchen, initialisiert alle benötigten Klassen.
     *  \param -
     *  \return `true` wenn die Initialisierung erfolgreich war, ansonsten `false`
     */
    bool start();

    /*! \brief Stellt alles auf dem Bildschirm dar. Alles. Das ganze Spiel.
     *  \param -
     *  \return -
     */
    void run();

    /*! \brief Gibt Speicher frei, beendet laufende Funktionen usw.
     *  \param -
     *  \return -
     */
    void stop();

private:

    IrrlichtDevice* device_;  // Zeiger auf das Entchen
#ifdef _DEBUG_MODE
    s32 fps_, lastFPS_;  // Hilfsvariable für FPS-Anzeige im Titel
#endif

    GameFloatControl();
    GameFloatControl( const GameFloatControl& );
    GameFloatControl& operator=( const GameFloatControl& );
    ~GameFloatControl();

    inline void createLogfile();
    inline void readConfig();
    bool createDeviceFromConfig();
#ifdef _DEBUG_MODE
    inline void printFPS();
#endif

};

#endif
