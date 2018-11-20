/*! \file TimeControl.h
 *  \brief zentrale Steuerung für übergebene Timer
 *  \note Bestandteil der Leviathan Engine
 */

#ifndef LEVIATHAN_CORE_TIMECONTROL_H
#define LEVIATHAN_CORE_TIMECONTROL_H

#include "Timer.h"
#include <cstdint>
#include <list>

namespace leviathan {
namespace core {

/*! \class TimeControl TimeControl.h "TimeControl.h"
 *  \brief zentrale Steuerung für übergebene Timer
 */
class TimeControl {
public:
  /*! \brief Konstruktor.
   */
  TimeControl() = default;

  /*! \brief Destruktor.
   *  \note Vorhandene Timer werden nicht gelöscht.
   */
  ~TimeControl() = default;

  TimeControl(const TimeControl &) = delete;
  TimeControl &operator=(const TimeControl &) = delete;

  /*! \brief Fügt einen vorhandenen Timer zur zentralen Steuerung hinzu.
   *  \param timer: Referenz auf den Timer
   */
  void add(Timer &timer);

  /*! \brief Entfernt einen Timer aus zentralen Steuerung.
   *  \note Timer wird nicht gelöscht.
   *  \param timer: Referenz auf den Timer
   */
  void remove(Timer &timer);

  /*! \brief Pausiert alle verwalteten Timer.
   */
  void pause();

  /*! \brief Lässt alle verwalteten Timer weiterlaufen.
   */
  void resume();

  /*! \brief Erhöht alle verwalteten Timer, z.B. um die seit dem letzten Tick vergangene Zeit.
   *  \param seconds: Zeitwert in Sekunden
   */
  void tick(const float seconds);

private:
  std::list<Timer *> timers_ = std::list<Timer *>();
};
} // namespace core
} // namespace leviathan

#endif
