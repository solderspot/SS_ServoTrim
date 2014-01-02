//
//  
//  AdafruitTrim.ino
//
// Copyright (c) 2014, Solder Spot
// All rights reserved. 

// This sketch requires the following libraries:
//   SS_ServoTrim: https://github.com/solderspot/SS_ServoTrim
//   Adafruit_PWMServoDriver: https://github.com/adafruit/Adafruit-PWM-Servo-Driver-Library

// include needed librarys
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SS_ServoTrim.h>


#define NUM_SERVOS 16

// create the servo driver instance
// change 0x40 to match your servo shield if necessary
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);  

SS_ServoTrim trim(NUM_SERVOS);


void setup() 
{
  // init serial port coms
  Serial.begin(9600);

   // init Adafruit's driver and set pulse frequency
  pwm.begin();
  pwm.setPWMFreq(50);  
  
  trim.setServoPulseRange( SS_ALL, 800, 2200);

  // set a variety of ranges
  trim.setServoPulseRange( 0, 1200, 1800);
  trim.setServoPulseRange( 1, 1000, 2000);
  trim.setServoPulseRange( 2, 900, 2100);
  trim.setServoPulseRange( 3, 800, 1600);
  trim.setServoPulseRange( 4, 1500, 1500);
  trim.setServoPulseRange( 5, 500, 2500);
  
  Serial.println("AdafruitTrim Ready!");
}

// main loop
void loop()
{
    for ( int i=0; i<NUM_SERVOS; i++)
    {
        setServoAngle(i, 0);
    }
    delay(2000);

    for ( int i=0; i<NUM_SERVOS; i++)
    {
        setServoAngle(i, 90);
    }
    delay(2000);
    for ( int i=0; i<NUM_SERVOS; i++)
    {
        setServoAngle(i, 180);
    }
    delay(2000);
}

void setServoAngle( int index, long angle)
{
  if (index >= 0 && index < NUM_SERVOS)
  {
    // 4096 ticks is 20,000 us (50Hz)
    long time = trim.getServoPulseTime(index, SS_DEGREES(angle));
    long ticks = (4096L*time)/20000L;
    // update the servo channel with the new pusle width
    pwm.setPWM(index, 0, ticks);

  }
}


