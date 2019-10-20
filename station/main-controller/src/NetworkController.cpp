#include "NetworkController.h"

#include <Arduino.h>
#include <SoftwareSerial.h>



NetworkController::NetworkController(int pinRx, int pinTx, String ssid, String pw){
    PIN_RX = pinRx;
    PIN_TX = pinTx;
    //establishConnection(ssid,pw);
}

void NetworkController::establishConnection(String ssid, String pw){
    String msg = "";
    msg += "$CONNECT";
    msg += "&SSID=" + ssid;
    msg += "&PW=" + pw;
    sendSerialMessage(msg);
}

void NetworkController::testConnection(){
    String msg = "§HTTP-GET%URL=http://192.168.178.195:5000/?name=Udo§";
    sendSerialMessage(msg);
}

void NetworkController::sendSerialMessage(String msg){
    Serial.println("send Command to esp8266...");
    SoftwareSerial wifiSerial(PIN_RX,PIN_TX);
    wifiSerial.begin(115200);
    wifiSerial.println(msg);
    delay(1000);
    String response = "reponse: ";
    while (wifiSerial.available()){
        response += wifiSerial.readString();
        delay(500);
    }
    Serial.println(response);
    
}

