 
//Densha de Go PS1 controller to USB Joystick using a Pro Micro board
//PSX function Pro Micro pin Controller pin
//Data         2             7
//Command      3             6

//  Copyright 2019 James van der Loeff
//  This program is free software: you can redistribute it and/or modify
//it under the terms of the GNU General Public License as published by
//the Free Software Foundation, either version 3 of the License, or
//(at your option) any later version.
//  This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.

//Libraries needed https://playground.arduino.cc/Main/PSXLibrary/ 
//                 https://github.com/MHeironimus/ArduinoJoystickLibrary

#include <Psx.h>
#include <Joystick.h>

#define dataPin 2
#define cmndPin 3
#define attPin 4
#define clockPin 5

Psx Psx;
//Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, 
//  JOYSTICK_TYPE_MULTI_AXIS, 5, 0,
//  true, true, false,
//  false, false, true,
//  false, true, 
//  false, false, false);
Joystick_ Joystick;

#define MASK_SPEED  0x080F
#define MASK_BREAK  0xF000
#define MASK_SELECT 0x80
#define MASK_START  0x10
#define MASK_A      0x100
#define MASK_B      0x200
#define MASK_C      0x400

#define SPEED_0  0x000F
#define SPEED_1  0x080E
#define SPEED_2  0x000E
#define SPEED_3  0x080B
#define SPEED_4  0x000B
#define SPEED_5  0x80A

#define BREAK0 0xD000
#define BREAK1 0x7000
#define BREAK2 0x5000
#define BREAK3 0xE000
#define BREAK4 0xC000
#define BREAK5 0x6000
#define BREAK6 0x4000
#define BREAK7 0xB000
#define BREAK8 0x9000
#define BREAK9 0x3000
#define BREAK10 0x1000
#define BREAK11 0xA000
#define BREAK12 0x8000
#define BREAK13 0x2000
#define BREAK14 0x0000

void setup() {
  Psx.setupPins(dataPin, cmndPin, attPin, clockPin, 20);
  pinMode(10,INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.setThrottleRange(0,255);
  Joystick.setRzAxisRange(0,255);
  Joystick.begin(false);
  Joystick.setThrottle(1);
  Joystick.setRzAxis(1);
  Joystick.setXAxis(512);
  Joystick.setYAxis(512);
  //Joystick.setZAxis(1);
  //Joystick.setThrottle(1);
  //Joystick.setRudder(1);
  Serial.begin(9600);
}

unsigned int data = 0; //Controller's response
char out[100];

void loop() {
  data = Psx.read();                                      // Psx.read() initiates the PSX controller and returns
  sprintf(out, "%4x\n", data);
                                                          // the button data
  Serial.print(out);                                   // Display the returned numeric value
  switch (data & MASK_SPEED)
    {
      case SPEED_0:
        Serial.println("P0");
        Joystick.setThrottle(1);
        break;
      case SPEED_1:
        Serial.println("P1");
        Joystick.setThrottle(153);
        break;
      case SPEED_2:
        Serial.println("P2");
        Joystick.setThrottle(170);
        break;
      case SPEED_3:
        Serial.println("P3");
        Joystick.setThrottle(200);
        break;
      case SPEED_4:
        Serial.println("P4");
        Joystick.setThrottle(230);
        break;
      case SPEED_5:
        Serial.println("P5");
        Joystick.setThrottle(255);
        break;
    }
    
    switch (data & MASK_BREAK)
    {
      case BREAK0:
        Serial.println("B0");
        Joystick.setRzAxis(1);
        break;
      case BREAK1:
        Serial.println("B1");
        Joystick.setRzAxis(32);
        break;
      case BREAK2:
        Serial.println("B2");
        Joystick.setRzAxis(64);
        break;
      case BREAK3:
        Serial.println("B3");
        Joystick.setRzAxis(96);
        break;
      case BREAK4:
        Serial.println("B4");
        Joystick.setRzAxis(100);
        break;
      case BREAK5:
        Serial.println("B5");
        Joystick.setRzAxis(128);
        break;
      case BREAK6:
        Serial.println("B6");
        Joystick.setRzAxis(160);
        break;
      case BREAK7:
        Serial.println("B7");
        Joystick.setRzAxis(192);
        break;
      case BREAK8:
        Serial.println("B8");
        Joystick.setRzAxis(224);
        break;
      case BREAK9:
        Serial.println("B9");
        Joystick.setRzAxis(255);
        break;
      case BREAK10:
        Serial.println("B10");
        Joystick.setRzAxis(255);
        break;
      case BREAK11:
        Serial.println("B11");
        Joystick.setRzAxis(255);
        break;
      case BREAK12:
        Serial.println("B12");
        Joystick.setRzAxis(255);
        break;
      case BREAK13:
        Serial.println("B13");
        Joystick.setRzAxis(255);
        break;
      case BREAK14:
        Serial.println("B14");
        Joystick.setRzAxis(255);
    }
    Joystick.setButton(0,(data&MASK_A)?1:0);
    Joystick.setButton(1,(data&MASK_B)?1:0);
    Joystick.setButton(2,(data&MASK_C)?1:0);
    Joystick.setButton(3,(data&MASK_SELECT)?1:0);
    Joystick.setButton(4,(data&MASK_START)?1:0);  
      Joystick.sendState();

      delay(15);
}
