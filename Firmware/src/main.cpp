#include <Arduino.h>
#include "wave.h"
#include "square.h"
#include "sine.h"

void setup() {
  setupWaves();
  setupSine();
  setupSquare();
}

FASTRUN void loop() {
  generateSines(10000, 10000);
}