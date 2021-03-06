#include "NetworkController.h"

#include <Arduino.h>
#include <SoftwareSerial.h>

#define SERIAL_BOUND_RATE 9600
String const SERVER_ADRESS="http://192.168.0.109:5000";

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
    String msg = "§HTTP-GET%URL=http://rklimpel.hopto.org:5000§";
    sendSerialMessage(msg);
}

void NetworkController::uploadTemperature(String temp){
    long time = millis();
    String body = "{"
        "\"value\":"+String(temp)+","
        "\"station_id\":0,"
        "\"unit\": \"C\","
        "\"sensor\": \"HT65XY\","
        "\"timestamp\": " + time+ ""
    "}";
    String msg = "§HTTP-POST%URL="+SERVER_ADRESS+"/api/v1.0/temperatures%BODY=" + body+ "§";

    sendSerialMessage(msg);
}

void NetworkController::sendSerialMessage(String msg){
    Serial.println("send Command to esp8266...");
    SoftwareSerial wifiSerial(PIN_RX,PIN_TX);
    wifiSerial.begin(SERIAL_BOUND_RATE);
    wifiSerial.println(msg);
    delay(1000);
    String response = "reponse: ";
    while (wifiSerial.available()){
        response += wifiSerial.readString();
        delay(500);
    }
    Serial.println(response);
    
}

