
/**********************************************************
  File: NanoSerial.h 
  
   Description: This sketch interfaces and controls the 
   MD25 - 12v 2.8A dual H-bridge motor driver
   Be the first to review this product

   Designed to work with our EMG30 gear motors, the MD25 will drive two motors.
   Controllled by Serial or the I2C Interface. 
   Two modes of operation, direct individual control of the motors or the ability to send a speed and a turn commands. 

   Voltage - 12v only. The 5v for the logic supplied from an on-board regulator, 300mA available for your own circuits. 
   Current - Up to 2.8A for each motor. 
   Encoder - Processes quadrature encoder inputs from motor. 360 counts per wheel turn when used with the EMG30.
   Size - 110mm x 52mm x 25mm 

   Note: This code assumes that an Arduino 2560 is used so that there are multiple serial ports to use, other that the 
   console serial_0 port

   RD02 = MD25 + EMG30 + Hardware & tires

  
 **********************************************************/

#include <math.h>

#include <Wire.h>



/*
Note:
 Not all pins on the Mega and Mega 2560 support change interrupts,
 so only the following can be used for RX:
 10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69

 Not all pins on the Leonardo and Micro support change interrupts,
 so only the following can be used for RX:
 8, 9, 10, 11, 14 (MISO), 15 (SCK), 16 (MOSI).   
*/



//--------------------------------------------------
//    Function declarations
//--------------------------------------------------
//void turnTowardsObject(action_enum turnDirection, int turnTime, int turnSpeed);
//void goForward(int speedVal, int leftMod, int rightMod, int commDelay);
void stopMotors();  
//void zeroEncoders();
//long readEncoder();
//byte readVolts();
//void readVI();


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
     
     // Get current azimuth angle with respect to start angle
//     gyroHeading = getGyroHeading(gyroHeading);       // get new heading, factor in drift over time, and limit to +/- 180 degrees
     
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
// Stop Motors
//**************************************************************************
void stopMotors() {
  NanoSerial.write(CMD);                   
  NanoSerial.write(STP);
}

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
  
  /*
  #ifdef DEBUG
  Serial.print("Encoder 1:");               // Displays data to the LCD03 screen
  Serial.print(result1,DEC);
  Serial.println(" ");                        // Print a blank space to clear any unwanted characters that are leftover on the LCD03 display
  
  delay(5);                                // Delay for LCD03 to process data
  
  Serial.print("Encoder 2:");
  Serial.print(result2,DEC);
  Serial.print(" ");
  #endif
 */ 
  return result1;                                   
}
