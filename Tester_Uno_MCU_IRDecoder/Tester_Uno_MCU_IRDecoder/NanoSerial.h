
/**********************************************************
  File: NanoSerial.h 
  
   Description: This header file defines the functions used
   to communicate with the ZenoRobotics' HDZ-SR H-Bridge
   motor controller processor.
  
 **********************************************************/

#include <math.h>

#include <Wire.h>


//**************************************************************************
// Stop Motors
//**************************************************************************
void stopMotors() {
  NanoSerial.write(CMD);                   
  NanoSerial.write(STP);
}

//***********************************************************************************
// Turns Left or Right For Sent Turn Time and Speed 
//***********************************************************************************
void turnTowardsObject(action_enum turnDirection, int turnTime, unsigned int turnSpeed)  {

     if ((turnDirection == adjust_left) || (turnDirection == turn_left)) {
        NanoSerial.write(CMD);                    
        NanoSerial.write(LFT);
        NanoSerial.write((byte)turnSpeed);
     }
     
     else if ((turnDirection == adjust_right) || (turnDirection == turn_right)) {
        NanoSerial.write(CMD);                    
        NanoSerial.write(RT);
        NanoSerial.write((byte)turnSpeed);
     }

     delay(turnTime);
     stopMotors();
     
}


//***********************************************************************************
// Go Forward
//***********************************************************************************
void goForward(int commDelay, unsigned int fwdSpd) {
  
     // write values to motors
     
     // left motor?
     NanoSerial.write(CMD);                   
     NanoSerial.write(FWD);
     NanoSerial.write((byte)fwdSpd);
     
     delay(commDelay); // commDelay
     

 
}

//***********************************************************************************
// Go Backward
//***********************************************************************************
void goBackward(int commDelay, unsigned int revSpd) {
  
     // write values to motors
     NanoSerial.write(CMD);                   
     NanoSerial.write(REV);
     NanoSerial.write((byte)revSpd);
     
     delay(commDelay);  //commDelay);
 
}


//**************************************************************************
// Encoder Functions
//**************************************************************************

void zeroEncoders() {
  NanoSerial.write(CMD);                   
  NanoSerial.write(RSTENCDRS);
}

long readEncoder1(){                        // Function to read and display the value of both encoders, returns value of first encoder

  long result1 = 0; 
  
  NanoSerial.write(CMD);
  NanoSerial.write(RDENCDR1);
  while(!NanoSerial.available()){}          // Wait for 4 bytes: encoder 1
  result1 = NanoSerial.read();                 // First byte for encoder 1, HH.
  result1 <<= 8;
  result1 += NanoSerial.read();                // Second byte for encoder 1, HL
  result1 <<= 8;
  result1 += NanoSerial.read();                // Third byte for encoder 1, LH
  result1 <<= 8;
  result1  += NanoSerial.read();               // Fourth byte for encoder 1, LL
 
  return result1;                                   
}
