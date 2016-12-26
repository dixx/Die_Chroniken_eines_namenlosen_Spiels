/*! \file TimeControl.h
 *  \brief zentrale Steuerung für übergebene Timer
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _TIMECONTROL_HEADER
#define _TIMECONTROL_HEADER

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
            TimeControl();

            /*! \brief Destruktor.
             */
            ~TimeControl();

            /*! \brief Fügt einen vorhandenen Timer zur zentralen Steuerung hinzu.
             *  \param timer: Referenz auf den Timer
             */
            void add( const Timer& timer );

            /*! \brief Entfernt einen Timer aus zentralen Steuerung.
             *  \note Timer wird nicht gelöscht.
             *  \param timer: Referenz auf den Timer
             */
            void remove( const Timer& timer );

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

        	irr::core::list<Timer> timerList_;
        	irr::core::list<Timer>::Iterator itr_;
        	irr::u32 timerCount_;
        	bool isPaused_;

            TimeControl( const TimeControl& );  // Objekt ist kopiergeschützt
            TimeControl& operator=( const TimeControl& );  // Objekt ist vor Zuweisung geschützt
        };
    }
}

#endif
