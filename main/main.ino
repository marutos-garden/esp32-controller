// This code controls the following devices:
// - NodeMCU 0.9 Board with ESP8266
// - DHT 11 Humidity and Temperature Sensor

#include <DHT.h>
#include <DHT_U.h>
#include "DHT.h"

//GPIO5
#define DHTPIN 5              
#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

//Data Storage
float humidity = 0;
float temperature = 0;
float heat_index = 0;
float solar_light = 0;

// Functions 
void getHumidityTemperature();
void printValues();

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  dht.begin();
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  getHumidityTemperature();
  printValues();   
  delay(1000);                      
  digitalWrite(LED_BUILTIN, HIGH);  
  delay(1000);                      
}

void getHumidityTemperature(){
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();
  if (isnan(humidity) || isnan(temperature)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }
  heat_index = dht.computeHeatIndex(temperature, humidity, false);
}

void printValues(){
  Serial.print(F("Humidity: "));
  Serial.print(humidity);
  Serial.print(F("% Temperature: "));
  Serial.print(temperature);
  Serial.print(F("°C "));
  Serial.print(F("Heat Index: "));
  Serial.print(heat_index);
  Serial.println(F("°C"));
}

