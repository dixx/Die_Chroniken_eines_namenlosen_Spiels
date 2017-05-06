/*! \file TimeControl.h
 *  \brief zentrale Steuerung für übergebene Timer
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _LEVIATHAN_TIMECONTROL_HEADER
#define _LEVIATHAN_TIMECONTROL_HEADER

#include <irrlicht.h>
#include "Timer.h"

namespace leviathan
{
    namespace core
    {

        /*! \class TimeControl TimeControl.h "TimeControl.h"
         *  \brief zentrale Steuerung für übergebene Timer
         */
        class TimeControl
        {
        public:

            /*! \brief Konstruktor.
             */
            TimeControl() {};

            /*! \brief Destruktor.
             */
            ~TimeControl();

            TimeControl( const TimeControl& ) = delete;
            TimeControl& operator=( const TimeControl& ) = delete;

            /*! \brief Fügt einen vorhandenen Timer zur zentralen Steuerung hinzu.
             *  \param timer: Referenz auf den Timer
             */
            void add( Timer& timer );

            /*! \brief Entfernt einen Timer aus zentralen Steuerung.
             *  \note Timer wird nicht gelöscht.
             *  \param timer: Referenz auf den Timer
             */
            void remove( Timer& timer );

            /*! \brief Pausiert alle verwalteten Timer.
             */
            void pause();

            /*! \brief Lässt alle verwalteten Timer weiterlaufen.
             */
            void resume();

            /*! \brief Erhöht alle verwalteten Timer um die seit dem letzten Tick vergangene Zeit.
             *  \param frameDeltaTime: Zeitwert in Sekunden
             */
            void tick( const irr::f32 frameDeltaTime );

        private:

        	irr::core::list<Timer*> timerList_;
        	irr::core::list<Timer*>::Iterator itr_;
        };
    }
}

#endif
