#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <fstream>
#include <string>

#include <SerialCommandHandler.h>


#define SERIAL_BOUND_RATE 9600

void runSetupHandler();
void indexHandler();
void startHandler();
void establishConnection(String ssid,String pw);
void executeCommand(String cmd);
void printAvailableNetworks();
const char* wifiStatusToString(wl_status_t status);
String getArgument(String argId,String cmd);
String sendPOSTRequest(String url, String body);
String sendGETRequest(String url);

ESP8266WebServer server(80);

void setup () {
    Serial.begin(SERIAL_BOUND_RATE);
    runSetupHandler();
}
 
void loop() {
    server.handleClient();
    if(Serial.available()){
       String cmd = Serial.readString();
       SerialCommandHandler().executeCommand(cmd);
    }
}

// ------------------ Microstation Setup ----------------------

void runSetupHandler(){
    Serial.println("");
    Serial.println("Starte WLAN-Hotspot \"Microstation-Setup\"");
    WiFi.mode(WIFI_AP);
    WiFi.softAP("Microstation-Setup");
    delay(500);
    Serial.print("IP Adresse "); 
    Serial.println(WiFi.softAPIP());
    
    server.on("/",indexHandler);
    server.on("/start",startHandler);
    server.begin();
}

void indexHandler(){
    //char content[] = "<form align=\"center\" action=\"/start\" method=\"POST\"><input type=\"submit\" value=\"Start Microstation\"></form>";
    char content[] = 
    "<form algin=\"center\" action=\"start\" method=\"get\">"
    "wifi-ssid: <input type=\"text\" name=\"ssid\"><br>"
    "wifi-pw: <input type=\"text\" name=\"pw\"><br>"
    "<input type=\"submit\" value=\"connect and start station\"></form>";

    server.send(200, "text/html",content);
}

void startHandler(){
    if( ! server.hasArg("ssid") || ! server.hasArg("pw") 
        || server.arg("ssid") == NULL || server.arg("pw") == NULL) {
        server.send(400, "text/plain", "400: Invalid Request");
        return;
    }

    
    server.send(200,"text/plain","Try to connect to '" + server.arg("ssid") + "'.\nIf connection fails this wifi will be up again in 30 sec.");
    delay(3);
    server.stop();
    server.close();
    establishConnection(server.arg("ssid"),server.arg("pw"));

}

void establishConnection(String newssid, String newpassword){
    Serial.println("Connect to '"+newssid+"' with pw '"+newpassword+"'");

    WiFi.mode(WIFI_STA);
    WiFi.begin(newssid, newpassword);

    Serial.print("Connecting to ");
    Serial.print(newssid); 
    Serial.println(" ...");

    int i = 0;
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(++i); Serial.print(' ');
        i++;
        if(i > 20){
            runSetupHandler();
        }
    }

    Serial.println('\n');
    Serial.println("Connection established!");  
    Serial.print("IP address:\t");
    Serial.println(WiFi.SSID());
    Serial.println(WiFi.localIP()); 
}