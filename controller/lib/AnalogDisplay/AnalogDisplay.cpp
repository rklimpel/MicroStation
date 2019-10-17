#include "AnalogDisplay.h"

#include<Arduino.h>

AnalogDisplay::AnalogDisplay(int pinLatch, int pinClock, int pinData,
            int firstDigitGnd, int secondDigitGnd, int thirdDigitGnd,int fourthDigitGnd){
    PIN_LATCH = pinLatch;
    PIN_CLOCK = pinClock;
    PIN_DATA = pinData;
    DIGIT_GND[0] = firstDigitGnd;
    DIGIT_GND[1] = secondDigitGnd;
    DIGIT_GND[2] = thirdDigitGnd;
    DIGIT_GND[3] = fourthDigitGnd;
    initPins();
}

void AnalogDisplay::initPins(){
    pinMode(PIN_LATCH,OUTPUT);
    pinMode(PIN_CLOCK,OUTPUT);
    pinMode(PIN_DATA,OUTPUT);
    pinMode(DIGIT_GND[0],OUTPUT);
    pinMode(DIGIT_GND[1],OUTPUT);
    pinMode(DIGIT_GND[2],OUTPUT);
    pinMode(DIGIT_GND[3],OUTPUT); 
}

void AnalogDisplay::toggleNumber(int digit, boolean on){
  if(on){
    digitalWrite(DIGIT_GND[digit-1],LOW);
  }else{
    digitalWrite(DIGIT_GND[digit-1],HIGH);
  }
}

void AnalogDisplay::display(char c,boolean setDot) {
  byte bits = 0;
  if(setDot){
    bits = addDot(convertToAnalogBits(c));
  } else {
    bits = convertToAnalogBits(c);
  }

  digitalWrite(PIN_LATCH,LOW);
  shiftOut(PIN_DATA,PIN_CLOCK,LSBFIRST,bits);
  digitalWrite(PIN_LATCH,HIGH); 
}

void AnalogDisplay::updateDigit(int digit,boolean setDot,char value){
  display(value,setDot);
  toggleNumber(digit,true);
  delay(DELAY_VISIBLITY);
  toggleNumber(digit,false);
}

void AnalogDisplay::printAnalogText(String text){

  int i = 0;
  boolean setDot = false;
  int dotOffset = 0;

  while(i < sizeof(text)){
    if(i+1 < sizeof(text) && text[i+1] == '.'){
      setDot = true;
    }

    if(text[i] != ' ' && text[i] != '.'){
        updateDigit(i+1-dotOffset,setDot,text[i]);
        if(setDot){
          setDot = false;
          dotOffset += 1;
        }
    }
    i+=1;
  }
}

void AnalogDisplay::updateDigits(int digits[], boolean dot,char value){
  for(int i = 0; i <= sizeof(digits)+1; i++){
    updateDigit(digits[i],dot,value);
  }
}

byte AnalogDisplay::addDot(byte input){
  return input | B00000001;
}

byte AnalogDisplay::convertToAnalogBits(char n) {
  if(n == ('0')){
    return B11111100;
  } else if (n == '1'){
    return B01100000;
  } else if (n == '2'){
    return B11011010;
  } else if (n == '3'){
    return B11110010;
  } else if (n == '4'){
    return B01100110;
  } else if (n == '5'){
    return B10110110;
  } else if (n == '6'){
    return B10111110;
  } else if (n == '7'){
    return B11100000;
  } else if (n == '8'){
    return B11111110;
  } else if (n == '9'){
    return B11110110;
  } else if (n == '-'){
    return B00000010;
  } else if (n == '_'){
    return B00010000;
  } else if (n == 'A'){
    return B11101110;
  } else if (n == 'B'){
    return B00111110;
  } else if (n == 'C'){
    return B10011100;
  } else if (n == 'D'){
    return B01111010; 
  } else if (n == 'E'){
    return B10011110;
  } else if (n == 'F'){
    return B10001110;
  } else if (n == 'H'){
    return B01101110;
   }else if (n == 'L'){
    return B00011100;
  } else if (n == 'P'){
    return B11001110;
  } else if (n == 'O'){
    return B11111100;
  } else if (n == 'U'){
    return B01111100;
  } else {
    return B10010010;
  }
}