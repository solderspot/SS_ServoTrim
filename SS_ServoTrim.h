//
//
// SS_ServoTrim.h
//
// Copyright (c) 2014, Solder Spot
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification,
// are permitted provided that the following conditions are met:
// 
// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.
// 
// * Redistributions in binary form must reproduce the above copyright notice, this
//   list of conditions and the following disclaimer in the documentation and/or
//   other materials provided with the distribution.
// 
// * Neither the name of the copyright holders nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
// ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
// ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
// ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


#ifndef _SS_ServoTrim_H
#define _SS_ServoTrim_H

#define SS_ServoTrimVersion        010000          // V1.0.0

#ifndef SS_ALL
#define SS_ALL          -1
#endif

#ifndef SS_DEGRESS
#define SS_DEGREES(D)        ((long)(((long)(D))*1000L))
#endif


struct SS_Trim; // private structure

class SS_ServoTrim
{

 public:

  // create servotrim with num_servo instacnes with default min max values for all servos
  SS_ServoTrim(int num_trims);

  // create servo trim with num_trim instacnes and new default min max values for all trims
  SS_ServoTrim(int num_trims, long minMicros, long maxMicros);

  // servo trim functions - trim index must be between 0..numTrims()-1, or SS_ALL to apply to all servo trims
  void setServoPulseRange( int trim_index, long minMicros, long maxMicros );    // set min and max pulse time in microseconds
  void setServoNumber ( int trim_index, long number );                          // associate a number with the servo
  void setServoData ( int trim_index, void *data);                              // associate data with the servo 

  // getters
  long              getServoPulseTime( int trim_index, long angle );   // map angle(in 1000ths degrees) to servo's pulse range
  long              getServoMaxPulseTime( int trim_index );            // get servo's max pulse time (microseconds)
  long              getServoMinPulseTime( int trim_index );            // get servo's min pulse time (microseconds)
  long              getServoNumber( int trim_index );                  // get servo's assigned number 
  void*             getServoData( int trim_index );                    // get servo's assigned data 

  // other
  int numTrims( void ) { return _num_trims;}


 private:

  SS_Trim          *_trim;
  int               _num_trims;

  SS_Trim          *get_trim(int index);
  void              init( int count);
 
};

#endif

