#ifndef ESPChipConnection_h
#define ESPChipConnection_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class ESPChipConnection {

    private:
        int PIN_RX;
        int PIN_TX;

        void waitForSerialCommand();

    public:
        ESPChipConnection(int pinRx, int pinTx);
        void connectToWifiNetwork(String ssid,String pw);
        void sendHTTPRequest(String ip,int port,String msg);

};

#endif