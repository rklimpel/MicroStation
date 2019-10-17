#include <Arduino.h>
#include <AnalogDisplay.h>

#define PIN_THERMISTOR 0
#define THERMISTOR_UPDATE_FREQUENZ 1500

String text;
long lastUpdate = 0;
AnalogDisplay display(11,9,12,1,2,3,4);

void loop() {

  if(millis()-lastUpdate>THERMISTOR_UPDATE_FREQUENZ){
    text = (String)readThermistor();
    lastUpdate = millis();
  }

  display.printAnalogText(text);
}

float readThermistor(){
  float temp = analogRead(PIN_THERMISTOR);
  temp = log(10000.0 * ((1024.0 / temp -1)));
  temp = 1/(0.001129148+(0.000234125+(0.0000000876741 * temp * temp)) * temp);
  temp = temp - 273.15;
  return temp;
}