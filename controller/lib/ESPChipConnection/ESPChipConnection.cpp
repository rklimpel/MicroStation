#include "ESPChipConnection.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial wifiSerial(0,0);

ESPChipConnection::ESPChipConnection(int pinRx, int pinTx){
    PIN_RX = pinRx;
    PIN_TX = pinTx;
    SoftwareSerial tmp(PIN_RX,PIN_TX);
    wifiSerial = tmp;
    wifiSerial.begin(9600);
    Serial.begin(9600);
    Serial.println("ESPChipConnection::ESPChipConnection");
}

void ESPChipConnection::connectToWifiNetwork(String ssid,String pw){
    //TODO
    wifiSerial.println("AT+CWJAP=\""+ssid+"\",\""+pw+"\"");
    waitForSerialCommand();
}

void ESPChipConnection::sendHTTPRequest(String ip,int port,String msg){
    Serial.println("ESPChipConnection::sendHTTPRequest");
    wifiSerial.println("AT+CIPSTART=\"TCP\",\""+ip+"\"," + (String)port + "\r\n");
    waitForSerialCommand();
    int msgLength = msg.length()+4;
    wifiSerial.println("AT+CIPSEND=" + (String)msgLength + "\r\n");
    waitForSerialCommand();
    wifiSerial.println(msg + "\r\n");
    waitForSerialCommand();
    wifiSerial.println("AT+CIPCLOSE\r\n");
    waitForSerialCommand();
}

void ESPChipConnection::waitForSerialCommand(){
    Serial.println("ESPChipConnection::waitForSerialCommand");
    int lastResponseBytes = 0;
    int i;
    while (lastResponseBytes != wifiSerial.available() && wifiSerial.available() != 0){
        lastResponseBytes=wifiSerial.available();
        Serial.println("waiting for cmd finish...");
        delay(400);
        i++;
        if(i>10){
            return;
        }
    }
}