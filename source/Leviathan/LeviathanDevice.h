/*! \file LeviathanDevice.h
 *  \brief Die eigentliche 'Leviathan Engine'.
 *         Bietet Zugriff auf alle Funktionalitäten, kümmert sich um Instanzierung ihrer Teile usw.
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_DEVICE_H
#define LEVIATHAN_DEVICE_H

#include "core/Configuration.h"
#include "core/GameStateManager.h"
#include "core/Logger.h"
#include "core/TimeControl.h"
#include "core/Randomizer.h"
#include "input/Actions.h"
#include "input/EventReceiver.h"
#include "irrlicht.h"

#ifndef NDEBUG
#    define LOG_FILE_NAME "game.log"
#else
#    define LOG_FILE_NAME "debug.log"
#endif

namespace TesthelperLeviathanDevice {
    class LeviathanDeviceWithIrrlichtMock;
}

namespace leviathan {

    /*! \class LeviathanDevice LeviathanDevice.h "LeviathanDevice.h"
     *  \brief Die eigentliche Engine.
     */
    class LeviathanDevice {

    public:
        /*! \brief Konstruktor. Initialisiert alle Bestandteile der Engine.
         */
        LeviathanDevice();

        /*! \brief Destruktor.
         */
        ~LeviathanDevice();

        LeviathanDevice(const LeviathanDevice&) = delete;
        LeviathanDevice& operator=(const LeviathanDevice&) = delete;

        /*! \brief Lädt die Konfiguration aus der angegebenen Datei und initialisiert alle Engine-Bestandteile damit.
         *  \param filename: Konfigdateiname
         */
        void init(const irr::io::path& fileName); // FIXME:: use ctor. that's what they are for.

        /*! \brief Der eigentliche Game-Loop.
         *         Diese Methode kümmert sich um das Aktualisieren und Zeichnen des aktuellen Spielzustandes,
         *         Berechnen der Zeit, Entscheiden ob die KI aktualisiert werden muss usw.
         */
        void run();

        /*! /brief Stoppt den Game-Loop.
         *  /note Der aktuelle Game-Loop läuft noch zu Ende durch.
         */
        void halt();

        /*! \brief Gibt das Errorlevel der Engine zurück.
         *  \return 0 wenn alles gut lief, ansonsten eine ganzzahlige positive Fehlernummer.
         */
        int exitStatus();

        /*! \brief Zugriff auf die TimeControl Instanz.
         */
        core::TimeControl& TimeControl();

        /*! \brief Zugriff auf den Logger.
         */
        core::Logger& Logger();

        /*! \brief Zugriff auf die aktuelle Konfiguration.
         */
        core::Configuration& Configuration();

        /*! \brief Zugriff auf die Verwaltung der Spielzustände.
         */
        core::GameStateManager& GameStateManager();

        /*! \brief Zugriff auf den Zufallszahlengenerator.
         */
        core::Randomizer& Randomizer();

        /*! \brief Zugriff auf Input-Mappings.
         */
        input::Actions& Actions();

        /*! \brief Zugriff auf Input-Events.
         */
        input::EventReceiver& EventReceiver();

    private:
        core::Logger* logger_ = nullptr;
        core::Configuration configuration_ = core::Configuration();
        irr::IrrlichtDevice* graphicEngine_ = nullptr;
        core::TimeControl timeControl_ = core::TimeControl();
        core::GameStateManager gameStateManager_ = core::GameStateManager();
        core::Randomizer randomizer_ = core::Randomizer();
        input::EventReceiver eventReceiver_ = input::EventReceiver();
        input::Actions actions_;

        friend TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock;  // now Irrlicht can be mocked in unit tests
    };
}

#endif
