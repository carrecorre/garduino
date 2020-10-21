
// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>
#include "DHT.h"
#include <TimeLib.h>

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22
#define SensorPin A0
#define BUTTON 4
#define RELAY 3

float sensorValue = 0;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DHT dht(DHTPIN, DHTTYPE);

Servo servoMotor;

int irrigations = 0;

void setup() {
  pinMode(RELAY, OUTPUT);
  pinMode(BUTTON, INPUT); 
  
  // set up the LCD's number of columns and rows:
  dht.begin();
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("Garduino");
}

void loop() {
  do{
     lcd.clear();
   lcd.print(digitalRead(BUTTON));
   delay(500);
  }while(1 != 0);
  
  delay(2000);
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();


  sensorValue = soilHumidity();

  printInfo(h, t, sensorValue);

  if (sensorValue > 700) {
    irrigate();
  }

}

float soilHumidity() {
  // Average from 100 sensor reads for more precision
  for (int i = 0; i <= 100; i++) {
    sensorValue = sensorValue + analogRead(SensorPin);
    delay(1);
  }
  sensorValue = sensorValue / 100.0;
  return sensorValue;

}

void irrigate() {

  lcd.clear();
  lcd.print(("REGANDO"));
  irrigations++;
  lcd.setCursor(0, 1);
  printIrrigations();
  digitalWrite(RELAY, HIGH);
  while (soilHumidity() > 600) {

  }
  digitalWrite(RELAY, LOW);
}

void printIrrigations() {
  lcd.print("Total riegos: ");
  lcd.print(irrigations);
}

void printInfo(float h, float t, float sensorValue) {

  lcd.clear();
  // print the number of seconds since reset:
  lcd.print(("H: "));
  lcd.print(h);
  lcd.print(("%"));
  lcd.setCursor(0, 1);
  lcd.print(("T: "));
  lcd.print(t);
  lcd.print((" C "));
  lcd.print(sensorValue);
}
