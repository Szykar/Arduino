/*
 https://github.com/Szykar/Arduino
 07-05-2017

 This sketch prints RPM count read from 
 hall effect sensor to the LCD.
 
 Circuit:
 -LCD 16x2
 -H137 Hall effect sensor
 */

#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int hallPin = 8;
const int ledPin = 13;

int hallState = 0;
unsigned long start = 0, period = 0;
unsigned int rpm;
bool last = true;

void setup() {
  pinMode(hallPin, INPUT);
  pinMode(ledPin, OUTPUT);
  digitalWrite(hallPin, HIGH);
  Serial.begin(9600);
  
  lcd.begin(16, 2);
  lcd.print("RPM METER");
  lcd.setCursor(0,1);
  for(int i=0;i<16;i++) {
    lcd.print("_");
    delay(100);
  }
  lcd.setCursor(0,0); 
  lcd.print("RPM 0   obr/min");
}

void rpms() {
   hallState = digitalRead(hallPin);
  
  if( hallState == HIGH ) {
    last = true;
  }
  else if (last == true)
  {
    period = millis()-start;
    rpm = (int) (1000.0/period*60);
    Serial.println(rpm);
    lcd.setCursor(4,0);
    lcd.print("   "); //clear previous reading
    lcd.setCursor(4,0);
    lcd.print(rpm);
    last = false;
    start = millis();
  }
  
  if(millis()-start > 10000)
    Serial.println("OFF"); 
}

void loop() {
  rpms();
}

