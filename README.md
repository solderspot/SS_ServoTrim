#SS_ServoTrim

ServoTrim is a companion library to [**SS_Servorator**](https://github.com/solderspot/SS_Servorator) but can also stand alone.

It is a very simple, even trivial library class. Its main purpose is to manage servo pulse timings for one or more servos. It also provides the ability to dynamically assign a number and associate data with each servo. 

ServoTrim's real usefulness is when one has to manage multiple servos in a systematic way.

##How it Works

Make sure to include the library header file:

	#include <SS_ServoTrim.h>

Let's assume we are using the Arduino Servo library to control 6 servos:

	#include <Servo.h>

	#define NUM_SERVOS		6
	
	Servo servos[NUM_SERVOS];


We would then create an instance of ServoTrim, passing in the number of servos we want to manage:

	SS_ServoTrim	trim(NUM_SERVOS);

[**Note:** We are not creating an array of trims. We are creating one 'trim' object that manages 6 servos.]

Now we create a function to set the position of a servo via a servo index and an angle:

	void setServoAngle( int index, int angle )
	{
		// instead of calling servo[index].write(angle)
		// we use the trim to set the pulse time using writeMicroseconds()
		servos[index].writeMicroseconds( trim.getServoPulseTime(index, SS_DEGREES(angle)));
	}
	
The function **getServoPulseTime()** returns the required pulse width (in microseconds) needed to move the servo to the specified angle 'angle'. The function takes two arguments. The first is the index of the trim to use and the second is the angle to move the servo to. 

**Note:** In SS_ServoTrim angles are in 1000ths of degrees so we need to multiple 'angle' by a 1000. The macro **SS_DEGREES()** does that for us.

So what pulse time does getServoPulseTime() return. By default it returns 1000 us for 0&deg; and 2000 us for 180&deg;. 1000 us is the minimum pulse width and 2000 us is the maximum pulse width.

You can query the trim for the current min and max pulse timings:

	long min = trim.getServoMinPilseTime( 0 );   // min time for trim 0
	long max = trim.getServoMaxPulseTime( 0 );   // max time for trim 0

Remember all timings are in microseconds.
	
You can adjust the min and max timings:

	trim.setServoPulseRange( 0, 500, 2500);
	
Now when you call trim.getServoPulseTime() it will return a value between 500 and 2500. 500 being 0&deg; and 2500 being 180&deg;	

You can use the constant **SS_ALL** to apply settings to all trims. For example:

	trim.setServoPulseRange( SS_ALL, 670, 2300);
	
will set all 6 of the trims to the range 670 us to 2300 us.

Also when you are instancing a ServoTrim object you can override the default range:

	SS_ServoTrim trim(NUM_SERVOS, 670, 2300);

## Adding Dynamic Mapping

ServoTrim allows us to assign numbers to each trim through a simple call:

	trim.setServoNumber( 0, 3);

You can query the servo number too:

	long number = trim.getServoNumber( 0 ); // returns 3
	
You can use this number for what every purposes you might need. One example might be to provide dynamic servo mapping at runtime.

If we modify or setServoAngle() function so:

	void setServoAngle( int index, int angle )
	{
		long servo_index = trim.getServoNumber( index );
		if( servo_index >= 0 && servo_index <NUM_SERVOS)
		{
			servos[servo_index].writeMicroseconds( trim.getServoPulseTime(index, SS_DEGREES(angle)));
		}
	}

We can use setServoNumber() to map 'index' to a different physical servo.

Servo numbers default to -1;
 
##Associating Data With Servos
 
Another useful pair of functions are:
 
	trim.setServoData( 0, mydata );
	void *data = trim.getServoData( 0 );
 	
You could use these function to do servo mapping too:

	trim.setServoData(0, &servos[3]);
	
	void setServoAngle( int index, int angle )
	{
		Servo *servo = (Servo*) trim.getServoData( index );
		if( servo )
		{
			servo->writeMicroseconds( trim.getServoPulseTime(index, SS_DEGRESS(angle)));
		}
	}
	
Servo data defaults to NULL.  	
   