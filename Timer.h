/*! \file Timer.h
 *  \brief Klasse stellt millisekundengenaue Timer bereit.
 */

#ifndef _TIMER_HEADER
#define _TIMER_HEADER

#include <irrlicht.h>

using namespace irr;

/*! \class Timer Timer.h "Timer.h"
 *  \brief  Schnittstelle für millisekundengenaue Timer.
 *  \note Instanzierung: `Timer* myTimer = new Timer( maxValue );` \n Benutzen: `myTimer->update( frameDeltaTime );`
 */
class Timer
{

public:

    /*! \brief Konstruktor.
     *  \param maxValue (\a const \a f32) Maximalwert in Sekunden
     *  \return -
     */
    Timer( const f32 maxValue );

    /*! \brief Destruktor.
     */
    ~Timer();

    /*! \brief Erhöht den Timer um bestimmten Wert (in Sekunden).
     *  \attention Muss nicht aufgerufen werden, wenn der Timer von TimerManager verwaltet wird!
     *  \param frameDeltaTime (\a const \a f32) Wert in Sekunden
     *  \return \a Timer* Zeiger auf sich selbst
     */
    Timer* tick( const f32 frameDeltaTime );

    /*! \brief Startet den Timer bei null.
     *  \param -
     *  \return -
     */
    void start();
    void restart();

    /*! \brief Stoppt und resettet den Timer.
     *  \param -
     *  \return -
     */
    void stop();

    /*! \brief Pausiert den Timer.
     *  \param -
     *  \return -
     */
    void pause();

    /*! \brief Lässt den Timer weiterlaufen.
     *  \param -
     *  \return -
     */
    void resume();

    /*! \brief Läuft der Timer gerade?
     *  \param -
     *  \return `true` wenn Timer läuft, ansonsten `false`
     */
    bool isRunning() const;

    /*! \brief Ist der Timer gerade pausiert?
     *  \param -
     *  \return `true` wenn Timer pausiert ist, ansonsten `false`
     */
    bool isPaused() const;

    /*! \brief Hat der Timer den Endwert erreicht/überschritten?
     *  \attention Timer wird bei Erreichen des Endwertes nicht automatisch zurückgesetzt oder angehalten!
     *             Dies ist z.B. nützlich um herauszufinden, wie lange der Endwert schon überschritten ist.
     *  \param -
     *  \return `true` wenn Timer fertig ist, ansonsten `false`
     */
    bool isFull() const;

    /*! \brief gibt den eingestellten Endwert zurück.
     *  \param -
     *  \return \a f32 Endwert in Sekunden
     */
    f32 getMaxValue() const;

private:

    f32 maxValue_;
    f32 currentValue_;
    bool timerIsRunning_;
    bool timerIsPaused_;

    Timer( const Timer& );  // Objekt ist kopiergeschützt
    Timer& operator=( const Timer& );  // Objekt ist vor Zuweisung geschützt

};

#endif
