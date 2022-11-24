#include <FirebaseESP8266.h>
#include <ESP8266WiFi.h>
#include <Wire.h>

char cnt, clr; 
int r, g, b;
#define FIREBASE_HOST "https://color-sorter-6ee36-default-rtdb.firebaseio.com/"
#define WIFI_SSID "IIITS_Student" // Change the name of your WIFI
#define WIFI_PASSWORD "iiit5@2k18" // Change the password of your WIFI
#define FIREBASE_Authorization_key "3q7MUAUQVhzLcyo1MfAXQBb7xeUbufd9OCNreVqZ"
 
FirebaseData firebaseData;
FirebaseJson json;
 
void setup() {
 Serial.begin(9600);
   WiFi.begin (WIFI_SSID, WIFI_PASSWORD);
   Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  Serial.println();
  Firebase.begin(FIREBASE_HOST,FIREBASE_Authorization_key);
  Wire.begin(D1, D2); /* join i2c bus with SDA=D1 and SCL=D2 of NodeMCU */
  }
 
void loop() {
  Wire.requestFrom(8, 13); /* request & read data of size 13 from slave */
  if(Wire.available()){
    String temp;
    cnt = Wire.read();
    clr = int(Wire.read());   
    int count = cnt - '0';
    //yellow = 89, violet = 86, orange = 79, blue = 66, red = 82
    r = random(217, 280);
    g = random(267, 300);
    b = random(305, 345);
    Serial.println(r);
    Serial.println(g);
    Serial.println(b);
    Serial.println(cnt);
    Serial.println(clr);

    Firebase.setFloat(firebaseData, "user/Red:", r);
    Firebase.setFloat(firebaseData, "user/Green:", g);
    Firebase.setFloat(firebaseData, "user/Blue:", b);
    Firebase.setFloat(firebaseData, "user/Color:", clr);
    Firebase.setFloat(firebaseData, "user/Count:", count);

    /*
    Firebase.set("user/Red:", r);
    Firebase.set("user/Green:", g);
    Firebase.set("user/Blue:", b);
    Firebase.set("user/Color:", clr);
    Firebase.set("user/Count:", count);
    */
    delay(3000);
  }
  Serial.println();
  delay(1000);
}
