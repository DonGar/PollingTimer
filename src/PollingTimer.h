#pragma once

/* PollingTimer library by dgarrett@acm.org

   This is a very light weight way to set a timer, and test to see if it
   has expired.

 */

#include "Particle.h"

class PollingTimer {
public:
  inline PollingTimer(unsigned long delay_millis) :
      _running(false), _delay(delay_millis) {};

  //
  // Control
  //

  inline void start() {
    this->_start = millis();
    this->_running = true;
  }

  inline void stop() {
    this->_running = false;
  }

  //
  // Status
  //

  // Is the timer current started?
  inline bool running() {
    return this->_running;
  }

  // How long as the timer been running, in millis?
  inline unsigned long waiting() {
    return this->running() ? millis() - this->_start : 0;
  }

  //
  // Results
  //

  // Returns true after the timer expires, then stops the timer. Always false
  // if the timer is stopped.
  inline bool expired() {
    bool result = this->_expired();
    if (result)
      this->stop();
    return result;
  }

  // Returns true exactly once each delay interval.
  //
  // min_delay:
  //  If true, wait for full delay before returning true again.
  //  If false, wait for delay from when previous interval expired.
  //
  // This is only relevant if you don't call interval() during the millisecond
  // in which the previous interval expired.
  inline bool interval( bool min_delay=true) {
    bool result = this->_expired();
    if (result) {
      if (min_delay)
        // Start over from right now. Re-fire after a full _delay.
        this->_start = millis();
      else
        // Start over as if we were called exactly on time.
        this->_start += this->_delay;
    }
    return result;
  }

  // Convenient helper for debouncing false -> true. Pass in the value to
  // debounce each loop. Returns true while the value is true and time >
  // debounce interval. Does not debounce true -> false. Do not use
  // start/stop.
  inline bool debounce(bool value) {
    if (value && !this->running())
      this->start();

    if (!value)
      this->stop();

    return this->_expired();
  }

private:
  inline bool _expired() {
    // This ordering is int overflow safe, as long as the actual time since
    // start isn't > ULONG_MAX (~50 days).
    return this->running() && (this->waiting() >= this->_delay);
  }

  bool _running;
  unsigned long _start;
  unsigned long _delay;
};
