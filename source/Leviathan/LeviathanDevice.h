/*! \file LeviathanDevice.h
 *  \brief Die eigentliche 'Leviathan Engine'.
 *         Bietet Zugriff auf alle Funktionalitäten, kümmert sich um Instanzierung ihrer Teile usw.
 *  \note Bestandteil der Leviathan Engine
*/

#ifndef _LEVIATHAN_DEVICE_HEADER
#define _LEVIATHAN_DEVICE_HEADER

#include <irrlicht.h>
#include "Configuration.h"
#include "Logger.h"
#include "TimeControl.h"

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

        /*! \brief Lädt die Konfiguration aus der angegebenen Datei und initialisiert alle Engine-Bestandteile damit.
         *  \param filename: Konfigdateiname
         */
        void init( const irr::io::path& fileName );

        /*! \brief Zugriff auf die TimeControl Instanz.
         */
        core::TimeControl& TimeControl();

        /*! \brief Zugriff auf den Logger.
         */
        core::Logger& Logger();

        /*! \brief Zugriff auf die aktuelle Konfiguration.
         */
        core::Configuration& Configuration();

    private:

        core::Configuration configuration_;
        irr::IrrlichtDevice* graphicEngine_;
        core::TimeControl timeControl_;
        core::Logger* logger_;
    };
}

#endif
