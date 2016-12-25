/*! \file Timer.h
 *  \brief millisekundengenauer Timer
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef _TIMER_HEADER
#define _TIMER_HEADER

#include <irrlicht.h>

namespace leviathan
{
    namespace core
    {

        /*! \class Timer Timer.h "Timer.h"
         *  \brief millisekundengenauer Timer
         */
        class Timer
        {

        public:

            /*! \brief Konstruktor.
             *  \param maxValue: Maximalwert in Sekunden
             */
            Timer( const irr::f32 maxValue );

            /*! \brief Erhöht den Timer um bestimmten Wert (in Sekunden).
             *  \attention Muss nicht aufgerufen werden, wenn der Timer von TimerManager verwaltet wird.
             *  \param frameDeltaTime: Zeit (in Sekunden)
             *  \return Referenz auf sich selbst
             */
            Timer& tick( const irr::f32 frameDeltaTime );

            /*! \brief Startet den Timer bei null.
             */
            void start();

            /*! \brief Restartet den Timer bei null.
             */
            void restart();

            /*! \brief Stoppt und setzt den Timer zurück.
             */
            void stop();

            /*! \brief Pausiert den Timer.
             */
            void pause();

            /*! \brief Lässt den Timer weiterlaufen.
             */
            void resume();

            /*! \brief Läuft der Timer gerade?
             *  \return `true` wenn Timer läuft, ansonsten `false`
             */
            bool isRunning() const;

            /*! \brief Ist der Timer gerade pausiert?
             *  \return `true` wenn Timer pausiert ist, ansonsten `false`
             */
            bool isPaused() const;

            /*! \brief Hat der Timer den Endwert erreicht/überschritten?
             *  \attention Timer wird bei Erreichen des Endwertes nicht automatisch zurückgesetzt oder angehalten!
             *  \return `true` wenn Timer fertig ist, ansonsten `false`
             */
            bool isFull();

            /*! \brief Gibt den eingestellten Endwert zurück.
             *  \return Endwert in Sekunden
             */
            irr::f32 getMaxValue() const;

        private:

            irr::f32 maxValue_;
            irr::f32 currentValue_;
            bool timerIsRunning_;
            bool timerIsPaused_;
            bool timerIsFull_;

            Timer( const Timer& );  // Objekt ist kopiergeschützt
            Timer& operator=( const Timer& );  // Objekt ist vor Zuweisung geschützt
        };

        /*! \class AlwaysRunningTimer
         *  \brief Schnittstelle für millisekundengenaue Timer, welche nicht zu stoppen sind.
         *  \attention Einmal gestartet, sind diese Timer durch nichts zu stoppen oder zu pausieren.
         *             Hilfreich wenn der Timer von TimerManager verwaltet wird.
         */
        class AlwaysRunningTimer : public Timer
        {

        public:

            /*! \brief Konstruktor.
             *  \param maxValue: Maximalwert in Sekunden
             */
            AlwaysRunningTimer( const irr::f32 maxValue ) : Timer(maxValue) {}

            /*! \brief Timer reagiert nicht auf stop.
             */
            void stop() {}

            /*! \brief Timer reagiert nicht auf pause.
             */
            void pause() {}

            /*! \brief Timer reagiert nicht auf resume.
             */
            void resume() {}

        private:

            AlwaysRunningTimer( const AlwaysRunningTimer& );  // Objekt ist kopiergeschützt
            AlwaysRunningTimer& operator=( const AlwaysRunningTimer& );  // Objekt ist vor Zuweisung geschützt
        };
    }
}

#endif
