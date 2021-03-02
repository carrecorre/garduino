// include the library code:
#include <LiquidCrystal.h>
#include <Servo.h>
#include "DHT.h"

#define DHTPIN 2     // Digital pin connected to the DHT sensor
#define DHTTYPE DHT22   // DHT 22

#define SensorPin A0
const int RELAY = 3;
// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
DHT dht(DHTPIN, DHTTYPE);

float sensorValue = 0;
float h = 0;
float t = 0;
float soilHumidity = 0;
int lecturas = 0;

Servo servoMotor;

void setup() {
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  // set up the LCD's number of columns and rows:
  dht.begin();
  lcd.begin(16, 2);

  // Print a message to the LCD.
  lcd.print("Garduino");

  h = dht.readHumidity();
  t = dht.readTemperature();
  soilHumidity = checkSoil();

}

void loop() {
  //30 min son 1.800.000 ms que son 900 vueltas
  //1 min son 60.000 ms que son 30 vueltas

  delay(2000);

  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 0);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  t = dht.readTemperature();
  //muestra el valor de la humedad actual aunque solo compruebe cada media hora para regar
  soilHumidity = analogRead(SensorPin);
  
  if (lecturas >= 900) {
    soilHumidity = checkSoil();
    lecturas = 0;
  }

  lcd.clear();
  lcd.print(("H: "));
  lcd.print(h);
  lcd.print(("%"));
  lcd.setCursor(0, 1);
  lcd.print(("T: "));
  lcd.print(t);
  lcd.print((" C "));
  lcd.print(soilHumidity);

  lecturas++;

}

float checkSoil() {
  // Average from 100 sensor reads for more precision
  for (int i = 0; i <= 100; i++) {
    sensorValue = sensorValue + analogRead(SensorPin);
    delay(1);
  }
  sensorValue = sensorValue / 100.0;

  if (sensorValue > 700) {
    irrigate();
  }

  return sensorValue;

}

void irrigate(){
    
    lcd.clear();
    lcd.print(("REGANDO"));
    digitalWrite(RELAY, HIGH);
   delay(10000);
    digitalWrite(RELAY, LOW);
  
  
}
