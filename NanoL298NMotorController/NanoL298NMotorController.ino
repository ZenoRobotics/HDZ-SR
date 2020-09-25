//*************************************************************
// File: NanoL298NMotorController.ino
// 
//--------------------------------------------------------------------------
// Written by Peter J. Zeno, Ph.D. <zenorobotics@gmail.com>, September 2020
//
// Copyright (C) ZenoRobotics, LLC - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential.
//--------------------------------------------------------------------------
//
// Sketch Description: 
// 
//   This sketch controls the digital side of the L298N motor drive
//   controller board module which drives two differential
//   DC steppers or DC motors using a dual channel H-bridge driver.
//
//   The sketch also reads the encoder of one of the motors using the
//   Encoder library. The instantiated encoder object requires two pins
//   that are connected to interrupts. Thus, for the Nano & Uno, these
//   are pins D2 & D3. Therefore, only one encoder can be read with this
//   setup. 
//
//   Otherwise, many of the commands used to setup the MD25 board are used here 
//   Reference: https://www.robot-electronics.co.uk/htm/md25ser.htm
//   The commands for this system are listed below.
//
// L298N Motor Drive Controller Board Description:
//
//   Dual-channel H-bridge driver working mode creates higher working efficiency,
//   L298N as main chip.Can drive one 2-phase stepper motor, one 4-phase stepper 
//   motor or two DC motors.
//
//   To avoid damaging the voltage stabilizing chip, please use an external 5V logic supply 
//   when using more than 12V driving voltage (remove 5v enable jumper!)...
//
//      a) The module has an on-board 78M05 5V regulator from STMicroelectronics. It can be 
//         enabled or disabled through a jumper.
//
//      b) When this jumper is in place, the 5V regulator is enabled, supplying logic power supply(Vss) 
//         from the motor power supply(Vs). In this case, 5V input terminal acts as an output pin and 
//         delivers 5V 0.5A. You can use it to power up the Arduino or other circuitry that requires 5V power supply.
//
//      c) When the jumper is removed, the 5V regulator gets disabled and we have to supply 5 Volts separately through 
//         5 Volt input terminal.
//
//   Use large-capacity filter capacitors and diode with freewheeling protection function, 
//   increasing reliability.
//
//   High working power to 35v, large current can reach 3A MAX and continue current is 2A, 
//   power to 25w.
//
//   Large capacity filter capacitance, afterflow protection diode, more stable and reliable. 
//
//*************************************************************

#include "common.h"
#include "nanoserial.h"


void setup()
 {
  Serial.begin(38400);     // Initialize 
  
  pinMode(pinLB,OUTPUT);   // left motor black wire
  pinMode(pinLR,OUTPUT);   // left motor red wire
  pinMode(pinRB,OUTPUT);   // right motor black wire
  pinMode(pinRR,OUTPUT);   // right motor red wire
  
  pinMode(pinMotorLPWM,  OUTPUT);  // Define pin for PWM output 
  pinMode(pinMotorRPWM,  OUTPUT);  // Define pin for PWM output

  zeroEncoders();

 }
 
    
void loop()
 {

   //Check for commands being sent 
   if (Serial.available() > 0) {
     getWriteValues();
     
   }

   delay(10);

 }

//-----------------------------------------------------------
// This function is called after the CMD hex value is recvd
// from the external processor connected to the serial port  
// of the motorcontroller Nano processor.
//-----------------------------------------------------------
void getWriteValues() { 

  long encoderCnt;
  char cmd_rcvd = " ";

  while(!Serial.available());
  cmd_rcvd = Serial.read(); // Get second command

    
    switch (cmd_rcvd) {
         case FWD:  // Forward
           while(!Serial.available());
           cmd_rcvd = Serial.read(); // Get motor speed value 0x0 to 0xFF command
           advance(cmd_rcvd);
           break;
           
         case REV:   // Backup
           while(!Serial.available());
           cmd_rcvd = Serial.read(); // Get motor speed value 0x0 to 0xFF command
           reverse(cmd_rcvd);
           break;
           
         case LFT:   // Left Turn
           while(!Serial.available());
           cmd_rcvd = Serial.read(); // Get motor speed value 0x0 to 0xFF command
           turnL(cmd_rcvd);
           break;
           
         case RT: // Right Turn
           while(!Serial.available());
           cmd_rcvd = Serial.read(); // Get motor speed value 0x0 to 0xFF command
           turnR(cmd_rcvd);
           break;

         case STP: // stop motors 
           stopMotors();
           break;

         case RDENCDR1: 
           encoderCnt = readEncoder1();
           //Serial.write(encoderCnt);
           Serial.write(encoderCnt>>24);
           Serial.write((encoderCnt>>16)&(0xff));
           Serial.write((encoderCnt>>8)&(0xff));
           Serial.write((encoderCnt)&(0xff));
           break;

         case RSTENCDRS: 
           zeroEncoders();
           break;
           
         default:
           // Code
           stopMotors();
           //Serial.print("Key Select = Unknown!!!\n");  //further debug on IR value captured and converted to unsigned int
           break;
       } // end of switch-case
  
}
