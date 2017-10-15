
#include "PollingTimer.h"

// If the digital read from pin D0 is true for >= 50 milliseconds, turn
// on pin D7. If D0 reads false, turn off D7.

const unsigned long MILLIS = 1000; // Long debounce to make it easier to see.

PollingTimer timer(MILLIS);

void setup() {
  pinMode(D0, INPUT_PULLDOWN);
  pinMode(D7, OUTPUT);

}

void loop() {
  bool input = timer.debounce(digitalRead(D0));
  digitalWrite(D7, input);
}
