
//  File: nanoserial.h 
//  
//  Sketch Description: This sketch interfaces and controls the 
//  L298N - Dual H-bridge DC motor driver
//
//--------------------------------------------------------------------------
// Written by Peter J. Zeno, Ph.D. <zenorobotics@gmail.com>, September 2020
//
// Copyright (C) ZenoRobotics, LLC - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential.
//--------------------------------------------------------------------------


#include <math.h>

#include <Wire.h>


void advance(unsigned int fwdSpeed)      // forward
    {
     digitalWrite(pinRR,HIGH);  
     digitalWrite(pinRB,LOW);  
     analogWrite(pinMotorRPWM,fwdSpeed);  //Set the output speed(PWM)
     digitalWrite(pinLR,HIGH); 
     digitalWrite(pinLB,LOW);   
     analogWrite(pinMotorLPWM,fwdSpeed);  //Set the output speed(PWM)
    }

void turnR(unsigned int trnSpeed)        //right
    {
     digitalWrite(pinRR,LOW);   
     digitalWrite(pinRB,HIGH);    
     analogWrite(pinMotorRPWM,trnSpeed);  //Set the output speed(PWM)
     digitalWrite(pinLR,HIGH);   
     digitalWrite(pinLB,LOW);    
     analogWrite(pinMotorLPWM,trnSpeed);  //Set the output speed(PWM)
    }

void turnL(unsigned int trnSpeed)         //left
    {
     digitalWrite(pinRR,HIGH);   
     digitalWrite(pinRB,LOW);    
     analogWrite(pinMotorRPWM,trnSpeed);  //Set the output speed(PWM)
     digitalWrite(pinLR,LOW);    
     digitalWrite(pinLB,HIGH);    
     analogWrite(pinMotorLPWM,trnSpeed);  //Set the output speed(PWM)
    }

void stopMotors()         //stop
    {
     digitalWrite(pinRR,LOW);
     digitalWrite(pinRB,LOW);
     digitalWrite(pinLR,LOW);
     digitalWrite(pinLB,LOW);
     analogWrite(pinMotorLPWM,0);
     analogWrite(pinMotorRPWM, 0);
    }
    
void reverse(unsigned int revSpeed)          //reverse
    {
     digitalWrite(pinRR,LOW);  
     digitalWrite(pinRB,HIGH);
     analogWrite(pinMotorRPWM,revSpeed);
     digitalWrite(pinLR,LOW);  
     digitalWrite(pinLB,HIGH);
     analogWrite(pinMotorLPWM,revSpeed);
    }

//**************************************************************************
// Zero out both Encoder Countts
//**************************************************************************
void zeroEncoders() {
  
   myEnc1.write(0);
 
} 
 

long readEncoder1(){                        // Function to read and display the value of both encoders, returns value of first encoder

  long newPosition1 = myEnc1.read();
   
  return newPosition1;                                   
}
