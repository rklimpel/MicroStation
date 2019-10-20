#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void testConnection();
void establishConnection();
void executeCommand(String cmd);
 
const char* ssid = "FRITZ!Box 7362 SL";
const char* password = "96716995986792895394";
 
void setup () {
 
  Serial.begin(115200);
  establishConnection();
 
}
 
void loop() {
   if(Serial.available()){
       String cmd = Serial.readString();
       Serial.println("received '" + cmd + "'");
       executeCommand(cmd);
   }
}

void executeCommand(String cmd){
    if(cmd.indexOf("$TEST") != -1){
        testConnection();
    }else if(cmd.indexOf("$CONNECT") != -1){
        establishConnection();
    }
}

void establishConnection(){
    WiFi.begin(ssid, password);
   
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
    }
}

void testConnection(){

    if (WiFi.status() == WL_CONNECTED) {

        Serial.println("Try sending request...");

        WiFiClient wifiClient;
        HTTPClient http;
        
        http.begin(wifiClient,"http://192.168.178.195:5000");
        int httpCode = http.GET();
        
        if (httpCode > 0) {
        
        String payload = http.getString();
        Serial.println(payload);
    
        }
    
        http.end();

    }
}