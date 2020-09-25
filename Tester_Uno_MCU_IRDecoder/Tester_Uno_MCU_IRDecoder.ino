//-------------------------------------------------------------------------------------
// File: Tester_Mega_MCU_IRDecoder.ino
//
// Description: 
//    This sketch/program resides on a MCU which communicates to the ZenoRobotics motor controller 
//    replacement for the NanoSerial. Designated IR remote key values, 2:Fwd, 8:Bwd, 4:Lft, 6:Rt, 5:Stop, are 
//    sent from an IR remote when the corresponding key is pressed. The key values are decoded and matched
//    to the desired motor actions. This sketch then sends the corresponding commands to the ZR H-Bridge motor controller unit,
//    which inturn, decodes these messages and sets the motor speeds and spin directions accordingly.
//
//-------------------------------------------------------------------------------------

#include "common.h"
#include <SoftwareSerial.h>

SoftwareSerial NanoSerial(SW_RX_PIN,SW_TX_PIN); // RX, TX
#include "NanoSerial.h"

// ================================================================
// ===                      INITIAL SETUP                       ===
// ================================================================

void setup() {
  int i = 0;

  Serial.begin(9600);
  
  // initialize the LED pin as an output:
  pinMode(IR_SIG_DECODED_IND_PIN,OUTPUT);
  

  receiver.enableIRIn(); // IR Remote receiver enable interrupts

    //-------------------------------------------------------------------------
    //                           MD25 Setup Section
    //-------------------------------------------------------------------------
    // configure system status io pins
 
    // Set serial communication baud rate between arduino & MD25 motor controller
    NanoSerial.begin(38400);
    delay(5);

    /*
    // Set mode to 2, Both motors controlled by writing to speed 1: *** For now.
    NanoSerial.write(CMD);                                            
    NanoSerial.write(SETMODE);
    NanoSerial.write(byte(0x00)); //2);              //(byte (0x00));
    delay(5);
    
    // Enable Regulator Feedback for encoder feedback to regulate power of motors
    NanoSerial.write(CMD);                                            
    NanoSerial.write(DISABLE_REGULATORS); //ENABLE_REGULATORS);
    delay(5);
    
    //
    NanoSerial.write(CMD);                         // Set MD25 accelleration value
    NanoSerial.write(WRITEACCEL);
    NanoSerial.write(MD25_Accel_Rate);             // From 1 to 10 steps per 25 ms
    delay(5);
    */

/*
    // Enable/Disable motors to keep turning after 2 seconds of non-communication with MD25 Motor Controller board
    NanoSerial.write(CMD);                                            
    NanoSerial.write(ENABLE_TIMEOUT);
    delay(5);

    byte  volts_byte  = readVolts();
    int   volts_whole = volts_byte/10;
    int   volts_fract = volts_byte%10;
    float volts = volts_whole + volts_fract/10;
*/    

    digitalWrite(IR_SIG_DECODED_IND_PIN,LOW);
    delay(500);

    for (i=0; i<3; i++) {
      digitalWrite(IR_SIG_DECODED_IND_PIN,HIGH);
      delay(500);
      digitalWrite(IR_SIG_DECODED_IND_PIN,LOW);
      delay(500);
    }

    zeroEncoders();
}


// ================================================================
// ===                    MAIN PROGRAM LOOP                     ===
// ================================================================


void loop() {


   getIRValue(); //test_drive_array[i]);  // rosserial func: calcSendOdomData(); embedded in case statement
   delay(80);
 
}


void getIRValue() { 
  
  unsigned int value; 

  digitalWrite(IR_SIG_DECODED_IND_PIN,LOW);
  
  if (receiver.decode(&output)) {
    value = output.value;
    digitalWrite(IR_SIG_DECODED_IND_PIN,HIGH);
    
    switch (value) {
         case zero:  // stop motors
           // Code
           stopMotors();                // non-delay command (other than 10ms)
           printIRRemoteDecodeValue(0);
           break;
           
         case one:   // zero encoders
           // Code
           zeroEncoders();                // non-delay command 
           printIRRemoteDecodeValue(1);
           break;
           
         case two:   // move forward (continuous)
           // Code
           goForward(2000, 100);  // non-delay command (other than 10ms)
           stopMotors();
           printIRRemoteDecodeValue(2);
           break;
           
         case three: // read encoders 
           // Code
           currEncoderVal1 = readEncoder1();
           Serial.print("EncoderL Value: ");
           Serial.println(currEncoderVal1);
           printIRRemoteDecodeValue(3);
           break;
           
         case four:  // point turn left - long
           // Code 
           stopMotors();               // non-delay command (other than 10ms)
           turnTowardsObject(adjust_left, 2000, 100); // non-delay command (other than 10ms)
           printIRRemoteDecodeValue(4);
           break;
           
         case five:   // stop motors
           // Code
           stopMotors();
           printIRRemoteDecodeValue(5);
           break;
           
         case six:    // point turn right - long
           // Code
           stopMotors();               // non-delay command (other than 10ms)
           turnTowardsObject(adjust_right, 2000, 100); // non-delay command (other than 10ms)
           printIRRemoteDecodeValue(6);
           break;
           
         case seven:  // point turn left - short
           // Code
           stopMotors();               // non-delay command (other than 10ms)
           turnTowardsObject(adjust_left, 2000, 100); // non-delay command (other than 10ms)
           printIRRemoteDecodeValue(7);
           break;
           
         case eight:   // move backwards (continuous)
           // Code
           goBackward(2000, 100);
           stopMotors();
           printIRRemoteDecodeValue(8);
           break;
           
         case nine:   // point turn right - short
           // Code
           stopMotors();               // non-delay command (other than 10ms)
           turnTowardsObject(adjust_right, 2000, 100); // non-delay command (other than 10ms)
           printIRRemoteDecodeValue(9);
           break;  
           
         default:
           // Code
           stopMotors();
           Serial.print("Key Select = Unknown!!!\n");
           break;
       } // end of switch-case

    //while (receiver.decode(&output))  // remove extra sent commands
      receiver.resume();
  }
  //receiver.resume();
  
  return pointTurn;
}


void printIRRemoteDecodeValue(unsigned int num) {
  
    Serial.print("Key Select = ");
    Serial.print(num);
    Serial.println();
    
}

 
