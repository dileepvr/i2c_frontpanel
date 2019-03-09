/* https://github.com/SpenceKonde/ATTinyCore */
/* pinout https://github.com/SpenceKonde/ATTinyCore/blob/master/avr/extras/ATtiny_x8.md */

#include <Wire.h>

int led1 = 1; // PD1
int led2 = 2; // PD2
boolean led1_state = false;
boolean led2_state = false;

int BCD_A = 9; // PB1
int BCD_B = 11; // PB3
int BCD_C = 12; // PB4
int BCD_D = 10; // PB2
int BCD_DP = 13; // PB5
int BCD_L0 = 5; // PD5
int BCD_L1 = 6; // PD6
int BCD_L2 = 7; // PD7
int BCD_L3 = 8; // PB0

int SW1 = 15; // PB7
int SW2 = 14; // PB6
//int SW3 = 26; // PA3
int SW4 = 25; // PA2
int SW5 = 4; // PD4
int SW6 = 3; // PD3

int button_state = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(BCD_A, OUTPUT);
  pinMode(BCD_B, OUTPUT);
  pinMode(BCD_C, OUTPUT);
  pinMode(BCD_D, OUTPUT);
  pinMode(BCD_DP, OUTPUT);
  pinMode(BCD_L0, OUTPUT);
  pinMode(BCD_L1, OUTPUT);
  pinMode(BCD_L2, OUTPUT);
  pinMode(BCD_L3, OUTPUT);
  pinMode(SW1, INPUT);
  pinMode(SW2, INPUT);
  //pinMode(SW3, INPUT);
  pinMode(SW4, INPUT);
  pinMode(SW5, INPUT);
  pinMode(SW6, INPUT);
  digitalWrite(led1, LOW);
  digitalWrite(led2, LOW);
  digitalWrite(BCD_DP, LOW);
  digitalWrite(SW1, LOW);
  digitalWrite(SW2, LOW);
  //digitalWrite(SW3, LOW);
  digitalWrite(SW4, LOW);
  digitalWrite(SW5, LOW);
  digitalWrite(SW6, LOW);
  digit0(10, '0'); digit0(10, '1'); digit0(10, '2'); digit0(10, '3'); // Blank

  Wire.begin(8);
  Wire.onReceive(receiveEvent);
  Wire.onRequest(requestEvent); 
}

void loop() { 
  delay(100);
  if (readbuttons() != 0) {
    button_state = readbuttons();
  }
}

void digit0(int num, char digit) {  
  digitalWrite(BCD_A, bitRead(num,0));
  digitalWrite(BCD_B, bitRead(num,1));
  digitalWrite(BCD_C, bitRead(num,2));
  digitalWrite(BCD_D, bitRead(num,3));  

  switch (digit) {
    case '0':
      digitalWrite(BCD_L0, HIGH);  
      digitalWrite(BCD_L0, LOW);
      break;
    case '1':
      digitalWrite(BCD_L1, HIGH);  
      digitalWrite(BCD_L1, LOW);
      break;
    case '2':
      digitalWrite(BCD_L2, HIGH);  
      digitalWrite(BCD_L2, LOW);
      break;    
    default:
      digitalWrite(BCD_L3, HIGH);  
      digitalWrite(BCD_L3, LOW);
  }

}

int readbuttons() {
  int output = 0;
  if(digitalRead(SW1) == 1) { output = 1; }
  if(digitalRead(SW2) == 1) { output = 2; }
  //if(digitalRead(SW3) == 1) { output = 3; }
  if(digitalRead(SW4) == 1) { output = 4; }
  if(digitalRead(SW5) == 1) { output = 5; }
  if(digitalRead(SW6) == 1) { output = 6; }
  return output;
}

void receiveEvent(int howMany) {
  char ff = Wire.read();
  if(ff == 'L') {
    if (Wire.available()) {
      while (1 < Wire.available()) { // loop through all but the last
        char c = Wire.read(); // receive byte as a character
      }
      int x = Wire.read();    // receive byte as an integer       
      if(x == '1') {
        led1_state = ~led1_state;
        if(led1_state) {
          digitalWrite(led1, HIGH);
        } else {
          digitalWrite(led1, LOW);
        }        
      } else if(x == '2') {
        led2_state = ~led2_state;
        if(led2_state) {
          digitalWrite(led2, HIGH);
        } else {
          digitalWrite(led2, LOW);
        }        
      }      
    }
  } else {
    while (1 < Wire.available()) { // loop through all but the last
      char c = Wire.read(); 
    }
    int x = Wire.read();    // receive byte as an integer
    digit0(x, ff);    
  }
  
}

void requestEvent() {
  
    switch (button_state) {
      case 1:
        Wire.write('1');
        break;
      case 2:
        Wire.write('2');
        break;
      case 3:
        Wire.write('3');
        break;
      case 4:
        Wire.write('4');
        break;
      case 5:
        Wire.write('5');
        break;
      case 6:
        Wire.write('6');
        break;        
      default:
        Wire.write('0');
    }
    button_state = 0;

}
