#include <Arduino.h>
#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL_DOUT_PIN = 4;
const int LOADCELL_SCK_PIN = 5;

HX711 scale;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  scale.set_scale(300);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  Serial.println(scale.get_units(), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
                                               // by the SCALE parameter set with set_scale
  Serial.println("Readings:");
}

void loop() {
  Serial.println(scale.get_units(), 1);
  delay(2500);
}
