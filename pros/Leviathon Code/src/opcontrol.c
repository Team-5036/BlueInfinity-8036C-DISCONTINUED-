/** @file opcontrol.c
 * @brief File for operator control code
 *
 * This file should contain the user operatorControl() function and any functions related to it.
 *
 * Copyright (c) 2011-2014, Purdue University ACM SIG BOTS.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Purdue University ACM SIG BOTS nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL PURDUE UNIVERSITY ACM SIG BOTS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Purdue Robotics OS contains FreeRTOS (http://www.freertos.org) whose source code may be
 * obtained from http://sourceforge.net/projects/freertos/files/ or on request.
 */

#include "main.h"



/*
 * Runs the user operator control code. This function will be started in its own task with the
 * default priority and stack size whenever the robot is enabled via the Field Management System
 * or the VEX Competition Switch in the operator control mode. If the robot is disabled or
 * communications is lost, the operator control task will be stopped by the kernel. Re-enabling
 * the robot will restart the task, not resume it from where it left off.
 *
 * If no VEX Competition Switch or Field Management system is plugged in, the VEX Cortex will
 * run the operator control task. Be warned that this will also occur if the VEX Cortex is
 * tethered directly to a computer via the USB A to A cable without any VEX Joystick attached.
 *
 * Code running in this task can take almost any action, as the VEX Joystick is available and
 * the scheduler is operational. However, proper use of delay() or taskDelayUntil() is highly
 * recommended to give other tasks (including system tasks such as updating LCDs) time to run.
 *
 * This task should never exit; it should end with some kind of infinite loop, even if empty.
 */

//[@author William Flint]
//Timer Values
//int Time_Rotate = 10;//amount of time in ??value
//Motor Ports
int Forward_Left = 2;
int Forward_Right = 3;
int Behind_Left = 8;
int Behind_Right = 9;
int Lift_Left = 4;
int Lift_Right = 5;
int Claw_Hand = 6;
int Claw_Rotate = 7;
//Define Joystick Buttons
#define Joy_Down	1//this works somehow?
#define Joy_Up		2
#define Joy_Left	3
#define Joy_Right	4
//Motor Designations
int Motor_Max = 127;
int Motor_Min = -127;
int Motor_Stop = 0;

void operatorControl() {

	while(1){
				/*//Beo-Wulf Drivetrain System\\
					//get joystick values for right and left thumbsticks*/
						int leftStick = -joystickGetAnalog(1, 3);
						int rightStick = joystickGetAnalog(1, 2);
					//setting the motor values
						motorSet(Forward_Left, leftStick);
						motorSet(Behind_Left, leftStick);
						motorSet(Forward_Right, rightStick);
						motorSet(Behind_Right, rightStick);
					//motor values are refreshed every 20ms
						delay(20);
					//ensure motors dont go above or below the max or min
					for(int p=0; p<=10;){
						p=p+1;
						if(motorGet(p)>Motor_Max){
							motorSet(p,Motor_Max);
							delay(20);
						}//end of if statement
						else if(motorGet(p)<Motor_Min){
						motorSet(p,Motor_Min);
							delay(20);
						}//end of else if statement

					}//end of for statement

				/*//_____________________________________________________________________\\
				//Buttons\\
				//button variables*/
					bool liftDown = joystickGetDigital(1,5, JOY_UP);
					bool liftUp = joystickGetDigital(1, 6, JOY_UP);
				//button if statements
					if(liftDown==1){
						motorSet(Lift_Left, Motor_Min);
						motorSet(Lift_Right, Motor_Max);
					}//end of if Statement
					else if(liftUp==1){
						motorSet(Lift_Left, Motor_Max);
						motorSet(Lift_Right, Motor_Min);
					} //end of else/if Statement
					//ensure that the lifts stop moving when buttons not pressed
					else{
						motorSet(Lift_Left, Motor_Stop);
						motorSet(Lift_Right, Motor_Stop);
					}//end of else statement
					/*//__________________________________________________________________________\\
					//Claw Stuff//
					//claw variables*/
					bool clawOpen = joystickGetDigital(1, 8, JOY_LEFT);
					bool clawClose = joystickGetDigital(1,8, JOY_RIGHT);
					bool clawStraight = joystickGetDigital(1,6,JOY_DOWN);
					bool clawRotated = joystickGetDigital(1,5,JOY_DOWN);
					//claw if statements
					if(clawOpen==1){
						motorSet(Claw_Hand, Motor_Max);
					}
					else if(clawClose==1){
						motorSet(Claw_Hand, Motor_Min);
					}
					else{
						motorSet(Claw_Hand, Motor_Stop);
					}
					//For Rotation
					if(clawStraight==1){
						/*for(int o=0; o<1;){
						int o=o+1;
						motorSet(Claw_Rotate, Motor_Max);
						}*/
						motorSet(Claw_Rotate,Motor_Max);
						delay(20);
						motorSet(Claw_Rotate,Motor_Stop);
					}
					else if(clawRotated==1){
						/*for(int z=0; z<1;){
							int z=z+1;
							motorSet(Claw_Rotate, Motor_Min);
						}*/
						motorSet(Claw_Rotate,Motor_Min);
						delay(20);
						motorSet(Claw_Rotate,Motor_Stop);
					}


	}//End of While Statement
}//void statement ending
