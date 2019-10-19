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
    Serial.write("ESPChipConnection::ESPChipConnection");
}

void ESPChipConnection::connectToWifiNetwork(String ssid,String pw){
    wifiSerial.println("AT");
    delay(5000);
    if(wifiSerial.find("OK")){
        wifiSerial.println("AT+CWMODE=3");
        delay(1000);
        String WF=String("AT+CWJAP=\"")+ssid+"\",\""+pw+"\"";
        wifiSerial.println(WF);
        delay(5000);
        Serial.println("Wifi Setup done.");
    }else {
        Serial.println("Wifi Setup failed.");
    }
}

void ESPChipConnection::sendHTTPRequest(String ip,int port,String msg){

    Serial.println("ESPChipConnection::sendHTTPRequest");
    sendATCommand("AT+CIPSTART=\"TCP\",\""+ip+"\"," + (String)port + "\r\n");
    int msgLength = msg.length()+4;
    sendATCommand("AT+CIPSEND=" + (String)msgLength + "\r\n");
    sendATCommand(msg + "\r\n");
    sendATCommand("AT+CIPCLOSE\r\n");
}

void ESPChipConnection::sendATCommand(String cmd){
    wifiSerial.println(cmd+"\r\n");
    while (wifiSerial.available()){
        Serial.println(wifiSerial.readString());
        while (Serial.availableForWrite()>0);  
    }
}

void ESPChipConnection::waitForSerialCommand(){
    Serial.println("ESPChipConnection::waitForSerialCommand");
    int lastResponseBytes = 0;
    int secondLastResponseBytes = 0;
    int i;
    while (lastResponseBytes != wifiSerial.available() 
            || secondLastResponseBytes != lastResponseBytes
            && wifiSerial.available() != 0){
        secondLastResponseBytes = lastResponseBytes;
        lastResponseBytes = wifiSerial.available();
        Serial.println("waiting for cmd finish...");
        delay(400);
        i++;
        if(i>10){
            return;
        }
    }
    
    String msg = "";
    while (lastResponseBytes != 0){
        msg+=(char)wifiSerial.read();
        lastResponseBytes--;
    }
    Serial.println("|START - " + msg + " - END|");
    
}