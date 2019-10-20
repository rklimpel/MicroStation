#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

void establishConnection(String ssid,String pw);
void executeCommand(String cmd);
String getArgument(String argId,String cmd);
String sendPOSTRequest(String url, String body);
String sendGETRequest(String url);
 
const char* ssid = "FRITZ!Box 7362 SL";
const char* password = "96716995986792895394";
 
void setup () {
  Serial.begin(115200);
  establishConnection(ssid,password);
}
 
void loop() {
   if(Serial.available()){
       String cmd = Serial.readString();
       executeCommand(cmd);
   }
}

void executeCommand(String cmd){
    Serial.println("CMD='"+cmd+"'");
    if(cmd.indexOf("§CONNECT") != -1){
        String ssid = getArgument(cmd,"SSID");
        String pw = getArgument(cmd,"PW");
        establishConnection(ssid,pw);
    }else if(cmd.indexOf("§HTTP-GET") != -1){
        String url = getArgument(cmd,"URL");
        String response = sendGETRequest(url);
        Serial.println("response="+response);
    }else if(cmd.indexOf("§HTTP-POST") != -1){
        String url = getArgument(cmd,"URL");
        String body = getArgument(cmd,"BODY");
        sendPOSTRequest(url,body);
    }
}

String getArgument(String cmd,String argId){
    String arg = "%"+argId+"=";
    int argStart = cmd.indexOf(arg)+arg.length();
    int argEnd = cmd.indexOf("%",argStart) > 0 ? cmd.indexOf("%",argStart) : cmd.indexOf("§",argStart);
    return cmd.substring(argStart,argEnd);
}

String sendGETRequest(String url){
    Serial.println("Start sending HTTP-GET to " + url + "...");
    String response;
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient wifiClient;
        HTTPClient http;
        http.begin(wifiClient,url);
        int httpCode = http.GET();  
        if (httpCode > 0) {
            response = http.getString();
        }else{
            response = "ERROR (http code " + (String)httpCode + ")";
        }
        http.end();
    }
    return response;
}

String sendPOSTRequest(String url, String body){
    Serial.println("Start sending HTTP-POST...");
    String response;
    if (WiFi.status() == WL_CONNECTED) {
        WiFiClient wifiClient;
        HTTPClient http;
        http.begin(wifiClient,url);
        http.addHeader("Content-Type", "text/plain");
        int httpCode = http.POST(body);  
        if (httpCode > 0) {
            response = http.getString();
        }else{
            response = "ERROR";
        }
        http.end();
    }
    return response;
}

void establishConnection(String ssid, String password){
    WiFi.begin(ssid, password);
   
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting...");
    }

    Serial.println("Connected to " + (String)ssid + ".");
}