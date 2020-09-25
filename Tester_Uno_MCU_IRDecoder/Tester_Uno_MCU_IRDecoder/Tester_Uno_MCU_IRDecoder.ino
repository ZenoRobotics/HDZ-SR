//-------------------------------------------------------------------------------------
// File: Tester_Mega_MCU_IRDecoder.ino
//
// Description: 
//    This sketch/program resides on a MCU which communicates to the ZenoRobotics motor controller 
//    replacement for the MD25. Designated IR remote key values, 2:Fwd, 8:Bwd, 4:Lft, 6:Rt, 5:Stop, are 
//    sent from an IR remote when the corresponding key is pressed. The key values are decoded and matched
//    to the desired motor actions. This sketch then sends the corresponding commands to the HDZ-SR H-Bridge 
//    motor controller unit, which inturn, decodes these messages and sets the motor speeds and spin directions 
//    accordingly.
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
    //                           HDZ-SR Setup Section
    //-------------------------------------------------------------------------
    // configure system status io pins
 
    // Set serial communication baud rate between arduino & HDZ-SR motor controller
    NanoSerial.begin(38400);
    delay(5);

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

      receiver.resume();
  }
  
}


void printIRRemoteDecodeValue(unsigned int num) {
  
    Serial.print("Key Select = ");
    Serial.print(num);
    Serial.println();
    
}

 
