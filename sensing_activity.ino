#include <SoftwareSerial.h>
SoftwareSerial btSerial(7,8);

int led = 3;

int sen1 = A0;
int sen2 = A2;
int sen3 = A4;

int value1 = 0;
int value2 = 0;
int value3 = 0;

int threshold = 500;

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  btSerial.begin(9600);
}

void loop() {
  value1 = analogRead(sen1);
  value2 = analogRead(sen2);
  value3 = analogRead(sen3);
 
  if(value1>threshold||value2>threshold||value3>threshold){
    digitalWrite(3,1);
    btSerial.write('1');
  }
  else{
    digitalWrite(3,0);
    btSerial.write('0');
  }

  delay(1000);
}