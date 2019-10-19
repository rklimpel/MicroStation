#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
 
const char* ssid = "FRITZ!Box 7362 SL";
const char* password = "96716995986792895394";
 
void setup () {
 
  Serial.begin(115200);
  WiFi.begin(ssid, password);
   
  while (WiFi.status() != WL_CONNECTED) {
   
    delay(1000);
    Serial.println("Connecting..");
   
  }
 
}
 
void loop() {
   
  if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    Serial.println("Try sending request...");

    WiFiClient wifiClient;
    HTTPClient http;  //Declare an object of class HTTPClient
     
    http.begin(wifiClient,"http://192.168.178.195:5000");  //Specify request destination
    int httpCode = http.GET();                                                                  //Send the request
     
    if (httpCode > 0) { //Check the returning code
     
      String payload = http.getString();   //Get the request response payload
      Serial.println(payload);                     //Print the response payload
 
    }
   
    http.end();   //Close connection
   
  }
   
  delay(10000);    //Send a request every 30 seconds
 
}