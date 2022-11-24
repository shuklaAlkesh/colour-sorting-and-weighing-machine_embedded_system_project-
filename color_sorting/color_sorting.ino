#include <Servo.h>
#include <Wire.h>

Servo pickServo;
Servo dropServo;

#define S0 4 
#define S1 5
#define S2 7
#define S3 6
#define sensorOut 8    

int frequency = 0;
int color = 0, correct = 1;
int o_count = 0, b_count = 0, v_count = 0, y_count = 0;
String str;

void setup() {
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  //frequency-scaling to 20% selected
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);
  pickServo.attach(10);
  dropServo.attach(9);
  Wire.begin(8);                /* join i2c bus with address 8 */
  Wire.onRequest(requestEvent); /* register request event */
  Serial.begin(9600);           
}

void loop() {
  //initial position of servo motor
   pickServo.write(135);
  delay(3000);
  for(int i = 135; i > 70; i--) {
    pickServo.write(i);
    delay(5);
  }
  delay(500);

  //color sensing
  color = detectColor();
  delay(1000);  
  
  switch (color) {
    case 1:
    dropServo.write(60);
    break;

    case 2:
    dropServo.write(80);
    break;

    case 3:
    dropServo.write(100);
    break;

    case 4:
    dropServo.write(120);
    break;

    case 0:
    break;

  }
  delay(500);

  //back to initial state
  if (color == 0) {
    correct = 0;
  } else {
    for(int i = 70; i > 0; i--) {
      pickServo.write(i);
      delay(5);
    } 
    delay(300);
    for(int i = 15; i < 135; i++) {
      pickServo.write(i);
      delay(5);
    }
  }

  color=0;
}

void requestEvent() {
  switch (color) {
    case 1:
    str = String(o_count);
    Wire.write(str.c_str());
    Wire.write("O");  
    break;

    case 2:
    str = String(v_count);
    Wire.write(str.c_str());
    Wire.write("V");  
    break;

    case 3:
    str = String(y_count);
    Wire.write(str.c_str());
    Wire.write("Y");  
    break;

    case 4:
    str = String(b_count);
    Wire.write(str.c_str());
    Wire.write("B");  
    break;

    case 0:
    break;

  }
}

int detectColor() {

  // activating red photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  frequency = pulseIn(sensorOut, LOW);
  int red = frequency;
  Serial.print("Red = ");
  Serial.print(frequency);//printing RED color frequency
  Serial.print("   ");
  delay(50);

   // activating blue photodiodes to read
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int blue = frequency;
  Serial.print("Blue = ");
  Serial.print(frequency);
  Serial.println("   ");
  delay(50);
  
  // activating green photodiodes to read
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  frequency = pulseIn(sensorOut, LOW);
  int green = frequency;
  Serial.print("Green = ");
  Serial.print(frequency);
  Serial.println("   ");
  delay(50);

  if((223<red&&red<243) && (316<green && green<343) && (287<blue&&blue<312)){ 
      color=1; 
      o_count++;
      Serial.println("Orange");
      Serial.print("Total orange objects detected so far: ");
      Serial.println(o_count);
      delay(5000);
  } else if((245<red&&red<260) && (320<green&&green<345) && (275<blue&&blue<300)){ 
      color=2;  
      v_count++;
      Serial.println("Violet");
      Serial.print("Total violet objects detected so far: ");
      Serial.println(v_count);
      delay(5000);
  } else if((210<red && red<240) && (285<green&&green<305) && (286<blue && blue<310)){ 
      color=3; 
      y_count++;
      Serial.println("Yellow");
      Serial.print("Total yellow objects detected so far: ");
      Serial.println(y_count);
      delay(5000);
  } else if((265<red && red<280) && (305<green&&green<335) && (267<blue && blue<290)){ 
      color=4; 
      b_count++;
      Serial.println("Blue");
      Serial.print("Total blue objects detected so far: ");
      Serial.println(b_count);
      delay(5000);
  } else {
      color=0; 
      Serial.println("No object placed");
  }
  return color;  
}
