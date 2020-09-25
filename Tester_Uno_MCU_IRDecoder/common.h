// File: common.h
//
  

//#define DEBUG 1

#include <IRremote.h>

//++++++++++++++++++++++++++++++++++++++++++++
// Serial Port Definitions
//++++++++++++++++++++++++++++++++++++++++++++
/* Mega 2560:
 * Serial1 on pins 19 (RX) and 18 (TX), 
 * Serial2 on pins 17 (RX) and 16 (TX), 
 * Serial3 on pins 15 (RX) and 14 (TX)
 */
// #define md25 Serial2     // only works when using MEGA2560
//----------------------------------------------
//----------    Pin Assignments   --------------
//----------------------------------------------
#define SW_RX_PIN                   2
#define SW_TX_PIN                   3
#define IR_RCVR_PIN                11 
#define IR_SIG_DECODED_IND_PIN     13


//----------------------------------------------
//------      End of Pin Assignments     -------
//----------------------------------------------

// Instantiate IR receiver
IRrecv receiver(IR_RCVR_PIN);
decode_results output;



//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//        Samsung BN59 Remote Codes
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
const unsigned int zero  = 34935;
const unsigned int one   = 8415;
const unsigned int two   = 41055;
const unsigned int three = 24735;
const unsigned int four  = 4335;
const unsigned int five  = 36975;
const unsigned int six   = 20655;
const unsigned int seven = 12495;
const unsigned int eight = 45135;
const unsigned int nine  = 28815;

unsigned int test_drive_array[] = {two, two, four, four, six, six, three}; 

// MD25 Command/Status addresses/data
#define CMD                 (byte)0x00              //  Start of command indicator (byte)

// Differential-Vector Based Motor Commands (Equal speed setting to both motors)
#define FWD                 0x21    // plus speed: 0x0 to 0xFF
#define REV                 0x22    // plus speed: 0x0 to 0xFF
#define LFT                 0x23    // plus speed: 0x0 to 0xFF
#define RT                  0x24    // plus speed: 0x0 to 0xFF
#define STP                 0x25
#define RDENCDR1            0x26
#define RDENCDR2            0x27
#define RSTENCDRS           0x28


//**************************************
//       Constants
//**************************************
const int16_t  gyroZOffset       =  -85;
const int    BarrierTurnTime     = 1100;   // ms
const int    MaxSpeed            =   25;
const int    TurnSpeed           =   43;
const int    fwdSpeed            =   43;
const int    bwdSpeed            =   43;
const int    AdjustTurnTime      =  400;   // ms
const int    AdjustTurnSpeed     =    4;
const int    commDelay           =    0;   // number of milliseconds delay before continuing program after writing to motor controller
const int    MD25_Accel_Rate     =    4;
const double maxGyroDelta        =    1.0;


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//       MD25 Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
double   loopTimer               = 0.0;
int      leftMotorSpeedMod       = 0;
int      rightMotorSpeedMod      = 0;
//byte   volts_byte;
//int    volts_whole;
//int    volts_fract;
//float  volts;
int      inByte;
long     currEncoderVal1         = 0;

double   knownAngle              = 0.0;
long     distanceBeforeTurn      = 0.0;  // Set in turnLeftRight() function, just prior to turn.
long     retDistance             = 0;
long     currEncoderVal          = 0;
bool     Home                    = false;
bool     HeadingHome             = false;

bool     pointTurn = false;

enum action_enum {
  stop_,
  go_straight,
  go_backward,
  turn_l_or_r,
  turn_left,
  turn_right,
  adjust_left,
  adjust_right
};

action_enum  nextAction = stop_;
