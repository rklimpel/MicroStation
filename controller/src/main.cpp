#include <Arduino.h>
#include <AnalogDisplay.h>
#include <SoftwareSerial.h>

#define PIN_THERMISTOR 0
#define THERMISTOR_UPDATE_FREQUENZ 1500
#define WIFI_UPDATE_FREQUENZ 5000

float readThermistor();
void doStuff();
void showSerialData();
void logSerialAvailable();

String text;
long lastUpdate = 0;
long lastWifiUpdate = 0;

AnalogDisplay analogDisplay(11,9,12,5,2,3,4);
SoftwareSerial wifiSerial(7,8);

void setup() {
  Serial.begin(9600);
}

void loop() {

  if(millis()-lastUpdate>THERMISTOR_UPDATE_FREQUENZ){
    text = (String)readThermistor();
    lastUpdate = millis();
  }

  if(millis()-lastWifiUpdate>WIFI_UPDATE_FREQUENZ){
    doStuff();
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

int response;

void doStuff(){
  wifiSerial.begin(9600);
  //wifiSerial.println("AT+CWJAP=\"Fritz!Box 7362 SL\",\"96716995986792895394\"")
  wifiSerial.println("AT+CIPSTART=\"TCP\",\"192.168.178.195\",5000\r\n");
  logSerialAvailable();
  wifiSerial.println("AT+CIPSEND=56\r\n");
  logSerialAvailable();
  wifiSerial.println("GET / HTTP/1.0\r\nHost: 192.168.178.195:5000\r\n\r\n\r\n");
  logSerialAvailable();
  wifiSerial.println("AT+CIPCLOSE\r\n");
  logSerialAvailable();
}

void showSerialData(){
  while (wifiSerial.available()){
    Serial.write(wifiSerial.read());
  }
}


void logSerialAvailable(){
  int lastAvailable = 0;
  int i;
  while (lastAvailable != wifiSerial.available() && wifiSerial.available() != 0){
    Serial.println("Not available... waiting...");
    lastAvailable=wifiSerial.available();
    delay(400);
    i++;
    if(i>10){
      return;
    }
  }
}