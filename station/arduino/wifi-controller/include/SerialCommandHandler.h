#ifndef SerialCommandHandler_h
#define SerialCommandHandler_h

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

class SerialCommandHandler {

    private:
        String getArgument(String cmd,String argId);
        String sendGETRequest(String url);
        String sendPOSTRequest(String url, String body);
        
        void printAvailableNetworks();
        const char* wifiStatusToString(wl_status_t status);

    public:
        void executeCommand(String cmd);
        void establishConnection(String newssid, String newpassword);
};

#endif