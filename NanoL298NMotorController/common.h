// File: common.h
//
//--------------------------------------------------------------------------
// Written by Peter J. Zeno, Ph.D. <zenorobotics@gmail.com>, September 2020
//
// Copyright (C) ZenoRobotics, LLC - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential.
//--------------------------------------------------------------------------

#include <Encoder.h>  

//#define DEBUG 1     //Uncomment for debug data to be sent to IDE Monitor
//----------------------------------------------
//----------    Pin Assignments   --------------
//----------------------------------------------

// Left (L) motor Forward  & Backward  depends on red&black wires top/bottom configurations & inX/inY assignments 
#define pinRR            7    //D7   // Pin In1  Left Motor Red Wire - OUT1
#define pinRB            8    //D8   // Pin In2  Left Motor Black Wire - OUT2
#define pinMotorRPWM     9    //D9   // Define RPWM Pin - ENA
// Right (R) motor Forward & Backward depends on red&black wires top/bottom configurations & inX/inY assignments
#define pinMotorLPWM     6    //D6   // Define LPWM Pin - ENB
#define pinLR            5    //D5   // Pin In3  Left Motor Red Wire - OUT3
#define pinLB            4    //D4   // Pin In4  Left Motor Black Wire - OUT4

//----------------------------------------------
//------      End of Pin Assignments     -------
//----------------------------------------------


// Change these two numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
Encoder myEnc1(2,3);   //D2,D3

//Encoder myEnc2(13,12);  // Only one encoder per chip/sketch seems to work.


long oldPosition1  = -999;
long oldPosition2  = -999;


// MD25 Command/Status addresses/data
#define CMD                 (byte)0x00              //  MD25 command byte of 0

// Differential-Vector Based Motor Commands (Equal speed setting to both motors)
#define FWD                 0x21
#define REV                 0x22
#define LFT                 0x23
#define RT                  0x24
#define STP                 0x25
#define RDENCDR1            0x26
#define RDENCDR2            0x27
#define RSTENCDRS           0x28


//************************************************
//   Variable registers written by commands
//   to Nano - Default settings given.
//************************************************

unsigned int Motor1SpeedReg         =   0;   // PWD "speed" settings 0 = full off, 255 = full on
unsigned int Motor2SpeedReg         =   0;   // PWD "speed" settings 0 = full off, 255 = full on
unsigned int TimeoutEnableReg       =   1;   // 1 = enabled (motor timeouts after 2 seconds); 0 = disabled
long         EncoderCountReg        =   0;
unsigned int AccelRateReg           =   4;

const unsigned    MAXSPEED          =   255;  //0 to FF hex

const int    commDelay    =    0;   // number of milliseconds delay before continuing program after writing to motor controller



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//       MD25 Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//byte   volts_byte;
//int    volts_whole;
//int    volts_fract;
//float  volts;
int      inByte;

enum action_enum {
  stop_,
  go_straight,
  go_backward,
  turn_left,
  turn_right
};

action_enum  nextAction = stop_;
