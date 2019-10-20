#include <Arduino.h>
#include <AnalogDisplay.h>
#include <NetworkController.h>

#define PIN_THERMISTOR 0
#define THERMISTOR_UPDATE_FREQUENZ 1500
#define WIFI_UPDATE_FREQUENZ 5000

#define WIFI_SSID "FRITZ!Box 7362 S"
#define WIFI_PW "96716995986792895394"

float readThermistor();
void doStuff();
void showSerialData();
void logSerialAvailable();

String text;
long lastUpdate = 0;
long lastWifiUpdate = 0;

AnalogDisplay analogDisplay(11,9,12,5,2,3,4);
NetworkController networkController(10,8,WIFI_SSID,WIFI_PW);

void setup() {
  Serial.begin(115200);
  Serial.println("setup done.");
}

void loop() {

  if(millis()-lastUpdate>THERMISTOR_UPDATE_FREQUENZ){
    text = (String)readThermistor();
    lastUpdate = millis();
  }

  if(millis()-lastWifiUpdate>WIFI_UPDATE_FREQUENZ){
    Serial.println("Testing Connection...");
    networkController.testConnection();
    lastWifiUpdate = millis();
  }

  analogDisplay.printAnalogText(text);
}

float readThermistor(){
  float temp = analogRead(PIN_THERMISTOR);
  temp = log(10000.0 * ((1024.0 / temp -1)));
  temp = 1/(0.001129148+(0.000234125+(0.0000000876741 * temp * temp)) * temp);
  temp = temp - 273.15;
  return temp;
}