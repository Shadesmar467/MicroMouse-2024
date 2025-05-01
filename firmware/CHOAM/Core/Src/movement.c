/*
 * movement.c
 *
 *  Created on: Apr 24, 2025
 *      Author: adamhwu, jpyong
 */

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "motors.h"
#include "values.h"
#include <math.h>

void moveLeftMotor(int direction, int speed) {
	SetLMotorDirection(direction);
	TIM2->CCR4 = fabsf(speed);
}

void moveRightMotor(int direction, int speed) {
	SetRMotorDirection(direction);
	TIM2->CCR3 = fabsf(speed);
}

int move_dist(float dist) {
	int targetL = encLmm + dist;
	int targetR = encRmm + dist;
	int direction = (dist > 0) ? 1 : 0;

	//int overshoot_dist = 10;

	while (encRmm < targetR || encLmm < targetL){
		if (encRmm < targetR * .75){
			moveRightMotor(direction, mouseSpeedR);
		}
		else if (encRmm < targetR){
			moveRightMotor(direction, biasVoltageR);
		}
		if (encLmm < targetL * .75) {
			moveLeftMotor(direction, mouseSpeedL);
		}
		else if (encLmm < targetL) {
			moveLeftMotor(direction , biasVoltageL);
		}
		continue;
	}

	TIM2->CCR4 = fabsf(0);	// right channel
	TIM2->CCR3 = fabsf(0);	// left channel


	while (encRmm > targetR) {
		moveRightMotor(0, biasVoltageR);
	}
	TIM2->CCR4 = fabsf(0);	// right channel

	return 0;
}

void frontStraighten() {
	while (dis_FL < dis_FL_30mm || dis_FR < dis_FR_30mm){
		if (dis_FL < dis_FL_30mm)
			moveLeftMotor(1, biasVoltageL + 20);
		if (dis_FR < dis_FR_30mm)
			moveRightMotor(1, biasVoltageR + 20);
	}
	moveLeftMotor(1, 0);
	moveRightMotor(1, 0);
}

void turn180() {
	int targetL = encLmm + 85;
	int targetR = encRmm - 95;
	while ((encLmm < targetL) && (encRmm > targetR)) {
		SetLMotorDirection(1);
		SetRMotorDirection(0);
		TIM2->CCR4 = fabsf(mouseSpeedR);
		TIM2->CCR3 = fabsf(mouseSpeedL);
	}
	TIM2->CCR4 = fabsf(0);
	TIM2->CCR3 = fabsf(0);
}

void turnLeft() {
	int targetL = encLmm + 170;
	while ((encLmm < targetL)) {
		SetLMotorDirection(1);
		TIM2->CCR4 = fabsf(mouseSpeedR);
		TIM2->CCR3 = fabsf(0);
	}
	TIM2->CCR4 = fabsf(0);
}

void turnRight() {
	int targetR = encRmm + 150; //right motor stronger than the left
	while ((encRmm < targetR)) {
		SetRMotorDirection(1);
		TIM2->CCR3 = fabsf(mouseSpeedL);
		TIM2->CCR4 = fabsf(0);
	}
	TIM2->CCR3 = fabsf(0);
}
