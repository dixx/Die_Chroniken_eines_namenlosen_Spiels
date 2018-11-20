/*! \file Timer.h
 *  \brief millisekundengenauer Timer
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_TIMER_H
#define LEVIATHAN_CORE_TIMER_H

namespace leviathan {
namespace core {

/*! \class Timer Timer.h "Timer.h"
 *  \brief millisekundengenauer Timer
 */
class Timer {

public:
  /*! \brief Konstruktor.
   *  \param maxValue: Maximalwert in Sekunden
   */
  explicit Timer(const float maxValue);

  /*! \brief Destruktor.
   */
  ~Timer() = default;

  Timer(const Timer &) = delete;
  Timer &operator=(const Timer &) = delete;

  /*! \brief Erhöht den Timer um bestimmten Wert (in Sekunden).
   *  \param seconds: Zeit (in Sekunden)
   *  \return Referenz auf sich selbst
   */
  Timer &tick(const float seconds);

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
  float getMaxValue() const;

private:
  float maxValue_;
  float currentValue_ = 0.0f;
  bool timerIsRunning_ = false;
  bool timerIsPaused_ = false;
  bool timerIsFull_ = false;
};

/*! \class AlwaysRunningTimer
 *  \brief Schnittstelle für millisekundengenaue Timer, welche nicht zu stoppen sind.
 *  \attention Einmal gestartet, sind diese Timer durch nichts zu stoppen oder zu pausieren.
 */
class AlwaysRunningTimer : public Timer {

public:
  /*! \brief Konstruktor.
   *  \param maxValue: Maximalwert in Sekunden
   */
  explicit AlwaysRunningTimer(const float maxValue) : Timer(maxValue) {}

  AlwaysRunningTimer(const AlwaysRunningTimer &) = delete;
  AlwaysRunningTimer &operator=(const AlwaysRunningTimer &) = delete;

  /*! \brief Timer reagiert nicht auf stop.
   */
  void stop() {}

  /*! \brief Timer reagiert nicht auf pause.
   */
  void pause() {}

  /*! \brief Timer reagiert nicht auf resume.
   */
  void resume() {}
};
} // namespace core
} // namespace leviathan

#endif
