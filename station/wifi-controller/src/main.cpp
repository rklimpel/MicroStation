#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void testConnection(String name);
void establishConnection(String ssid,String pw);
void executeCommand(String cmd);
String getArgument(String argId,String cmd);
 
const char* ssid = "FRITZ!Box 7362 SL";
const char* password = "96716995986792895394";
 
void setup () {
  Serial.begin(115200);
  establishConnection(ssid,password);
}
 
void loop() {
   if(Serial.available()){
       String cmd = Serial.readString();
       Serial.println("received '" + cmd + "'");
       executeCommand(cmd);
   }
}

void executeCommand(String cmd){
    if(cmd.indexOf("TEST") != -1){
        String name = getArgument(cmd,"NAME");
        testConnection(name);
    }else if(cmd.indexOf("CONNECT") != -1){
        String ssid = getArgument(cmd,"SSID");
        String pw = getArgument(cmd,"PW");
        establishConnection(ssid,pw);
    }
}

String getArgument(String cmd,String argId){
    String arg = "&"+argId+"=";
    int argStart = cmd.indexOf(arg)+arg.length();
    int argEnd = cmd.indexOf("&",argStart) > 0 ? cmd.indexOf("&",argStart) : cmd.indexOf("$",argStart);
    return cmd.substring(argStart,argEnd);
}

void establishConnection(String ssid, String password){
    WiFi.begin(ssid, password);
   
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
    }

    Serial.println("Connected to " + (String)ssid + ".");
}

void testConnection(String name){

    Serial.println("name="+name);

    if (WiFi.status() == WL_CONNECTED) {

        Serial.println("Try sending request...");

        WiFiClient wifiClient;
        HTTPClient http;
        
        http.begin(wifiClient,"http://192.168.178.195:5000/?name="+name);
        int httpCode = http.GET();
        
        if (httpCode > 0) {
        
        String payload = http.getString();
        Serial.println(payload);
    
        }
    
        http.end();

    }
}