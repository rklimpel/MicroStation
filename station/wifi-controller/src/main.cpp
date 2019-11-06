#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

#define SERIAL_BOUND_RATE 9600

void establishConnection(String ssid,String pw);
void executeCommand(String cmd);
void printAvailableNetworks();
const char* wifiStatusToString(wl_status_t status);
String getArgument(String argId,String cmd);
String sendPOSTRequest(String url, String body);
String sendGETRequest(String url);
 
const char* ssid = "Zum Einhornland";
const char* password = "Butterbreadcoffee23";
 
void setup () {
  Serial.begin(SERIAL_BOUND_RATE);
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
    }else if(cmd.indexOf("§PRINT-NETWORKS") != -1){
        printAvailableNetworks();
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
        http.addHeader("content-type", "application/json");
        int httpCode = http.POST(body);  
        if (httpCode > 0) {
            response = http.getString();
        }else{
            response = "ERROR";
        }
        Serial.println("Got return code " + String(httpCode));
        Serial.println("Response: " + response);
        http.end();
    }
    return response;
}

void establishConnection(String newssid, String newpassword){
    Serial.println("Connect to '"+newssid+"' with pw '"+newpassword+"'");

    WiFi.begin(newssid, newpassword);

    Serial.print("Connecting to ");
    Serial.print(newssid); 
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) { // Wait for the Wi-Fi to connect
        delay(1000);
        Serial.print(++i); Serial.print(' ');
    }

    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP()); 
}

void printAvailableNetworks(){

    int numberOfNetworks = WiFi.scanNetworks();
 
    for(int i =0; i<numberOfNetworks; i++){
 
        Serial.print("Network name: ");
        Serial.println(WiFi.SSID(i));
        Serial.print("Signal strength: ");
        Serial.println(WiFi.RSSI(i));
        Serial.println("-----------------------");
 
    }
}

const char* wifiStatusToString(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}