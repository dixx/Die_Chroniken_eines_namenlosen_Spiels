/*! \file TimerManager.h
 *  \brief Klasse (Singleton) stellt Schnittstelle für Timer bereit.
 */

#ifndef _TIMERMANAGER_HEADER
#define _TIMERMANAGER_HEADER

#include "leviathan.h"

/*! \class TimerManager TimerManager.h "TimerManager.h"
 *  \brief  Schnittstelle für Timer.
 *
 *  Dieser Manager kann beliebig viele Timer erzeugen und steuern.
 *  \attention Klasse ist `Singleton`.
 *  \note Instanzierung: `TimerManager& myTimerManager = TimerManager::getInstance();`
 *        \n Oder: `TimerManager::getInstance();`
 *        \n Benutzen: `myTimerManager.createTimer(30);`
 *        \n Oder: `TimerManager::getInstance().pause();`
 */
class TimerManager
{

public:

    /*! \brief Ersatz für den Konstruktor.
     *
     *  Instanziert die Klasse einmalig und verhindert Mehrfachinstanzierung.
     *  \param -
     *  \return Referenz auf die einzige Instanz dieser Klasse
     */
    static TimerManager& getInstance();

    /*! \brief Erstellt einen neuen von TimerManager verwalteten Timer.
     *  \param maxValue (\a const \a f32) maximaler Zeitwert in Sekunden
     *  \return \a Timer* Zeiger auf den erzeugten Timer
     */
    leviathan::core::Timer* createTimer( const irr::f32 maxValue );

    /*! \brief Entfernt einen Timer aus der Verwaltung und löscht ihn.
     *  \note Timer wird nicht gelöscht, wenn er nicht von TimerManager erstellt wurde!
     *  \param timer (\a Timer*) Zeiger auf den zu entfernenden Timer
     *  \return -
     */
    void removeTimer( leviathan::core::Timer* timer );

    /*! \brief Pausiert alle von TimerManager verwalteten Timer.
     *  \param -
     *  \return -
     */
    void pause();

    /*! \brief Lässt alle von TimerManager verwalteten Timer weiterlaufen.
     *  \param -
     *  \return -
     */
    void resume();

    /*! \brief Erhöht alle von TimerManager verwalteten Timer um die seit dem letzten Tick vergangene Zeit.
     *  \param frameDeltaTime (\a const \a f32) Zeitwert in Sekunden
     *  \return -
     */
    void tick( const irr::f32 frameDeltaTime );

private:

	irr::core::list<leviathan::core::Timer*> timerList_;
	irr::core::list<leviathan::core::Timer*>::Iterator itr_;
	irr::u32 timerCount_;
	bool isPaused_;

    TimerManager();
    TimerManager( const TimerManager& );
    TimerManager& operator=( const TimerManager& );
    ~TimerManager();

};

#endif
