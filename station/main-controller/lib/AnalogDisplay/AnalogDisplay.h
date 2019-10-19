#ifndef AnalogDisplay_h
#define AnalogDisplay_h

#include <Arduino.h>

#define DELAY_VISIBLITY 1

class AnalogDisplay {

    private:
        int PIN_LATCH;  //74HC595 STCP
        int PIN_CLOCK;  //74HC595 SHCP
        int PIN_DATA;   //74HC595 DS+
        int DIGIT_GND[4];

        void toggleNumber(int digit, boolean on);
        void display(char c,boolean setDot);
        void updateDigit(int digit,boolean setDot,char value);
        void updateDigits(int digits[], boolean dot,char value);
        void initPins();
        byte addDot(byte input);
        byte convertToAnalogBits(char n);

    public:
        AnalogDisplay(int pinLatch, int pinClock, int pinData, 
            int firstDigitGnd, int secondDigitGnd, int thirdDigitGnd,int fourthDigitGnd);
        void printAnalogText(String text);

};

#endif