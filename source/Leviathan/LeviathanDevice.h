/*! \file LeviathanDevice.h
 *  \brief Die eigentliche 'Leviathan Engine'.
 *         Bietet Zugriff auf alle Funktionalitäten, kümmert sich um Instanzierung ihrer Teile usw.
 *  \note Bestandteil der Leviathan Engine
*/

#ifndef _LEVIATHAN_DEVICE_HEADER
#define _LEVIATHAN_DEVICE_HEADER

#include <irrlicht.h>
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

        /*! \brief
         */
        core::TimeControl& getTimeControl();

        /*! \brief
         */
        core::Logger& getLogger();

    private:

        irr::IrrlichtDevice* graphicEngine_;
        core::TimeControl timeControl_;
        core::Logger* logger_;
    };
}

#endif
