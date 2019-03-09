#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);

  char p;
  if(Serial.available() > 0) {
    p = Serial.read();
    if(p == 'B') {
      Wire.requestFrom(8, 1);    // request 1 byte from slave device #8

      if(Wire.available()) {
        Serial.print("Received: ");
        while (Wire.available()) { // slave may send less than requested
          char c = Wire.read(); // receive a byte as character
          Serial.print(c);         // print the character
        }
        Serial.println();
      }
    } else if (p != '\n') {
      Wire.beginTransmission(8);
      Wire.write(p);
      while(Serial.available() > 0) {
        char c = Serial.read();
        if(c != '\n') {
          //Wire.beginTransmission(8);
          Wire.write(c);
          //Wire.endTransmission();
          //Serial.write(c);    
        }
      }
      Wire.endTransmission();
      Serial.println("Sent.");
    }
  }

}
