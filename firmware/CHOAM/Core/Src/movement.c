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

// hehebruh
int move_dist(float dist) {
	int targetL = encLmm + dist;
	int targetR = encRmm + dist;
	int direction = (dist > 0) ? 1 : 0;

	while ((encRmm < targetR) || (encRmm > targetR+10) || (encLmm < targetL) || (encLmm > targetL + 10)) {
		if (encRmm < targetR){
			SetRMotorDirection(direction);
			TIM2->CCR4 = fabsf(mouseSpeedR);
		}
		else if (encRmm > targetR + 10){
			SetRMotorDirection(!direction);
			TIM2->CCR4 = fabsf(biasVoltageR + 20);
		}
		if (encLmm < targetL) {
			SetLMotorDirection(direction);
			TIM2->CCR3 = fabsf(mouseSpeedL);
		}
		else if (encLmm > targetL + 10) {
			SetLMotorDirection(!direction);
			TIM2->CCR3 = fabsf(biasVoltageL + 20);
		}
		continue;
	}

//	while ((encRmm < targetR) || (encLmm < targetL)) {
//		if (encRmm < targetR){
//			SetRMotorDirection(direction);
//			TIM2->CCR4 = fabsf(mouseSpeedR);
//		}
//		else {
//			TIM2->CCR4 = fabsf(0);	// right channel
//		}
//
//		if (encLmm < targetL) {
//			SetLMotorDirection(direction);
//			TIM2->CCR3 = fabsf(mouseSpeedL);
//		}
//		else {
//			TIM2->CCR3 = fabsf(0);	// right channel
//		}
//		continue;
//	}

	TIM2->CCR4 = fabsf(0);	// right channel
	TIM2->CCR3 = fabsf(0);	// left channel

	return 0;
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
