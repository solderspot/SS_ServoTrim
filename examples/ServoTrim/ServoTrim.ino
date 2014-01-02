//
//  
//  ServoTrim.ino
//
// Copyright (c) 2014, Solder Spot
// All rights reserved. 

// This sketch requires the following library:
//   SS_ServoTrim: https://github.com/solderspot/SS_ServoTrim

// include needed librarys
#include <Servo.h>
#include <SS_ServoTrim.h>


#define NUM_SERVOS 6

Servo servos[NUM_SERVOS];
SS_ServoTrim trim(NUM_SERVOS);


void setup() 
{
  // init serial port coms
  Serial.begin(9600);

  // assign PWM pins to servos
  servos[0].attach(3);
  servos[1].attach(5);
  servos[2].attach(6);
  servos[3].attach(9);
  servos[4].attach(10);
  servos[5].attach(11);

  // set a variety of ranges
  trim.setServoPulseRange( 0, 1200, 1800);
  trim.setServoPulseRange( 1, 1000, 2000);
  trim.setServoPulseRange( 2, 900, 2100);
  trim.setServoPulseRange( 3, 800, 1600);
  trim.setServoPulseRange( 4, 1500, 1500);
  trim.setServoPulseRange( 5, 500, 2500);
  
  Serial.println("ServoTrim Ready!");
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
    long time = trim.getServoPulseTime(index, SS_DEGREES(angle));
    servos[index].writeMicroseconds( time );

    Serial.print("servo[");
    Serial.print(index);
    Serial.print("] ");
    Serial.print(angle);
    Serial.print(" is ");
    Serial.print(time);
    Serial.println(" us");
  }
}

