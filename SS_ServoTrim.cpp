//
//  
//  SS_ServoTrim.cpp
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

#if ARDUINO >= 100
 #include "Arduino.h"
#else
 #include "WProgram.h"
#endif

#include <stdlib.h> // for malloc and free

#include "SS_ServoTrim.h"


struct SS_Trim
{
     long                   number;
     long                   minTime;
     long                   maxTime;
     void                   *data;
};

//----------------------------------------
//
//----------------------------------------

SS_ServoTrim::SS_ServoTrim(int count)
{
    init(count);
}

//----------------------------------------
//
//----------------------------------------

SS_ServoTrim::SS_ServoTrim(int count, long min, long max)
{
    init(count);
    setServoPulseRange( SS_ALL, min, max);
}

//----------------------------------------
//
//----------------------------------------

void SS_ServoTrim::init( int count )
{
    // create servo array
    _trim = (SS_Trim*)malloc(sizeof(SS_Trim)*count);
    _num_trims = count;

    // init trim data
    SS_Trim *t = _trim;
    for ( int i=0; i<_num_trims;i++, t++)
    {
        t->data = NULL;
        t->maxTime = 2000;
        t->minTime = 1000;
        t->number = -1;
    }
}

//----------------------------------------
//
//----------------------------------------

void SS_ServoTrim::setServoPulseRange( int index, long min, long max )
{
    if ( index == SS_ALL)
    {
        for (int i=0;i<_num_trims;i++ )
        {
            setServoPulseRange( i, min, max );
        }

        return;
    }

    SS_Trim *trim = get_trim(index);
    if ( trim && min <= max )
    {
        trim->maxTime = max;
        trim->minTime = min;
    }
}

//----------------------------------------
//
//----------------------------------------

void SS_ServoTrim::setServoNumber ( int index, long number )
{
    if ( index == SS_ALL)
    {
        for (int i=0;i<_num_trims;i++ )
        {
            setServoNumber( i, number);
        }

        return;
    }

    SS_Trim *trim = get_trim(index);
    if ( trim )
    {
        trim->number = number;
    }
}

//----------------------------------------
//
//----------------------------------------

void SS_ServoTrim::setServoData ( int index, void *data)
{
    if ( index == SS_ALL)
    {
        for (int i=0;i<_num_trims;i++ )
        {
            setServoData( i, data);
        }

        return;
    }

    SS_Trim *trim = get_trim(index);
    if ( trim )
    {
        trim->data = data;
    }
}

//----------------------------------------
//
//----------------------------------------

long SS_ServoTrim::getServoPulseTime( int index, long angle )
{
    SS_Trim *trim = get_trim(index);
    if ( !trim )
    {
        return -1;
    }

    return map(angle, 0, 180000L, trim->minTime, trim->maxTime);
}

//----------------------------------------
//
//----------------------------------------

long SS_ServoTrim::getServoMaxPulseTime( int index )
{
    SS_Trim *trim = get_trim(index);
    return trim ? trim->maxTime : -1;
}

//----------------------------------------
//
//----------------------------------------

long SS_ServoTrim::getServoMinPulseTime( int index )
{
    SS_Trim *trim = get_trim(index);
    return trim ? trim->minTime : -1;
}

//----------------------------------------
//
//----------------------------------------

long SS_ServoTrim::getServoNumber( int index )
{
    SS_Trim *trim = get_trim(index);
    return trim ? trim->number : -1;
}

//----------------------------------------
//
//----------------------------------------

void*SS_ServoTrim::getServoData( int index )
{
    SS_Trim *trim = get_trim(index);
    return trim ? trim->data : NULL;
}

//----------------------------------------
//
//----------------------------------------

SS_Trim *SS_ServoTrim::get_trim( int index)
{
    return (index >= 0 && index < _num_trims && _trim ) ? _trim+index : NULL;
}


