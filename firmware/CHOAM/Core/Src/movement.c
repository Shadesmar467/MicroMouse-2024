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
	float startencL = encLmm;
	float startencR = encRmm;
	int direction = (dist > 0) ? 1 : 0;

	while (encRmm < dist+startencR || encLmm < dist+startencL){
		// Right motor profile
		if (encRmm-startencR < dist * .6){
			moveRightMotor(direction, 370);
		}
		else if (encRmm-startencR < dist){
			moveRightMotor(direction, 130);
		}
		else{
			moveRightMotor(direction, 0);
		}

		// Left motor profile
		if (encLmm-startencL < dist * .6) {
			moveLeftMotor(direction, 370);
		}
		else if (encLmm-startencL < dist) {
			moveLeftMotor(direction , 130);
		}
		else{
			moveLeftMotor(direction, 0);
		}
		continue;
	}

	moveRightMotor(direction, 0);
	moveLeftMotor(direction, 0);
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

void turn(int rightDir) {
	float targetL = (rightDir) ? encLmm + turnTicksL : encLmm - turnTicksL;
	float targetR = (rightDir) ? encRmm - turnTicksR : encRmm + turnTicksR;

	if (rightDir){
		while ((encRmm > targetR) || (encLmm < targetL)) {
			if (encRmm > targetR) {
				moveRightMotor(0, biasVoltageR + 50);
			}
			else {
				moveRightMotor(0, 0);
			}

			if (encLmm < targetL) {
				moveLeftMotor(1, biasVoltageL + 50);
			}
			else {
				moveLeftMotor(1, 0);
			}
		}
		moveLeftMotor(0,0);
		moveRightMotor(0,0);
	}

	else {
		while ((encRmm < targetR) || (encLmm > targetL)) {
			if (encRmm < targetR) {
				moveRightMotor(1, biasVoltageR + 50);
			}
			else {
				moveRightMotor(1, 0);
			}

			if (encLmm > targetL) {
				moveLeftMotor(0, biasVoltageL + 50);
			}
			else {
				moveLeftMotor(0, 0);
			}
		}
		moveLeftMotor(0,0);
		moveRightMotor(0,0);
	}
	HAL_Delay(500);
}
