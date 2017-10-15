
#include "PollingTimer.h"

// If the digital read from pin D0 is true for >= 50 milliseconds, turn
// on pin D7. If D0 reads false, turn off D7.

const unsigned long MILLIS = 1000;

PollingTimer timer(MILLIS);

void setup() {
  pinMode(D7, OUTPUT);
  digitalWrite(D7, 0);

  // The intervals will never fire if you don't start the timer.
  timer.start();
}

bool led = false;

void loop() {
  if (timer.interval()) {
    led = !led;
    digitalWrite(D7, led);
  }
}
