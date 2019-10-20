#ifndef ESPChipConnection_h
#define ESPChipConnection_h

#include <Arduino.h>
#include <SoftwareSerial.h>

class NetworkController {

    private:
        int PIN_RX;
        int PIN_TX;
        String ssid;
        String pw;

        void sendSerialMessage(String msg);
        void establishConnection(String ssid, String pw);

    public:
        NetworkController(int pinRx, int pinTx, String ssid, String pw);
        void testConnection();
};

#endif