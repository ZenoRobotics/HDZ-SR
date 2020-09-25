// File: common.h
//
  

//#define DEBUG 1

#include <IRremote.h>

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


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//       MD25 Variables
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int      inByte;
long     currEncoderVal1         = 0;

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
