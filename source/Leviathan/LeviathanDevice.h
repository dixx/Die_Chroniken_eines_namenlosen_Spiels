/*! \file LeviathanDevice.h
 *  \brief Die eigentliche 'Leviathan Engine'.
 *         Bietet Zugriff auf alle Funktionalitäten, kümmert sich um Instanzierung ihrer Teile usw.
 *  \note Bestandteil der Leviathan Engine
*/

#ifndef _LEVIATHAN_DEVICE_HEADER
#define _LEVIATHAN_DEVICE_HEADER

#include "irrlicht.h"
#include "Actions.h"
#include "Configuration.h"
#include "EventReceiver.h"
#include "IActionConsumer.h"
#include "IEventProducer.h"
#include "IEventConsumer.h"
#include "GameStateManager.h"
#include "Logger.h"
#include "TimeControl.h"

#ifndef NDEBUG
    #define LOG_FILE_NAME "game.log"
#else
    #define LOG_FILE_NAME "debug.log"
#endif

namespace TesthelperLeviathanDevice { class LeviathanDeviceWithIrrlichtMock; } // forward declaration for unit tests

namespace leviathan
{

    /*! \class LeviathanDevice LeviathanDevice.h "LeviathanDevice.h"
     *  \brief Die eigentliche Engine.
     */
    class LeviathanDevice
    {

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
        void init(const irr::io::path& fileName);

        /*! \brief Der eigentliche Game-Loop.
         *         Diese Methode kümmert sich um das Aktualisieren und Zeichnen des aktuellen Spielzustandes,
         *         Berechnen der Zeit, Entscheiden ob die KI aktualisiert werden muss usw.
         */
        void run();

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

    private:

        core::Configuration configuration_;
        irr::IrrlichtDevice* graphicEngine_;
        core::TimeControl timeControl_;
        core::GameStateManager gameStateManager_;
        core::Logger* logger_;
        core::EventReceiver eventReceiver_;

        friend TesthelperLeviathanDevice::LeviathanDeviceWithIrrlichtMock; // now Irrlicht can be mocked in unit tests
    };
}

#endif
