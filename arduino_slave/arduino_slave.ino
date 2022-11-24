#include <Wire.h>

void setup() {
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           /* start serial for debug */
}

void loop() {
  delay(100);
}

// function that executes whenever data is requested from master
void requestEvent() {
  int cnt = 9;
  String str4 = String(cnt);
  Wire.write(str4.c_str());
  Wire.write("V");  /*send string on request */
  
}
