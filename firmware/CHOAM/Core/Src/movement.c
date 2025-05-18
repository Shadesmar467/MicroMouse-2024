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
#include "distance.h"
#include <math.h>

void moveLeftMotor(int direction, int speed) {
	SetLMotorDirection(direction);
	TIM2->CCR4 = fabsf(speed);
	mouseSpeedL = speed;
}

void moveRightMotor(int direction, int speed) {
	SetRMotorDirection(direction);
	TIM2->CCR3 = fabsf(speed);
	mouseSpeedR = speed;
}

void stopMotors() {
	moveRightMotor(0, 0);
	moveLeftMotor(0, 0);
}

int move_dist(float dist) {
	float startencL = encLmm;
	float startencR = encRmm;
	int direction = (dist > 0) ? 1 : 0;

	while (encRmm < dist+startencR || encLmm < dist+startencL){
		// Right motor profile
		if (encRmm-startencR < dist * .6){
			moveRightMotor(direction, mouseSpeedR);
		}
		else if (encRmm-startencR < dist){
			moveRightMotor(direction, 100);
		}
		else{
			moveRightMotor(!direction, 80);
		}

		// Left motor profile
		if (encLmm-startencL < dist * .6) {
			moveLeftMotor(direction, mouseSpeedL);
		}
		else if (encLmm-startencL < dist) {
			moveLeftMotor(direction , 100);
		}
		else{
			moveLeftMotor(!direction, 80);
		}

		if (dis_FL < 40 || dis_FR < 40) {
			break;
		}

		continue;
	}

	moveRightMotor(direction, 0);
	moveLeftMotor(direction, 0);
	return 0;
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

void corridor_correction() {
	float lnew, rnew, error, p_term, d_term, correction;
	int max_correct, min_correct;
	// error is high if closer to right, low if close to left
	error = dis_SL - dis_SR;
	// p term is proportional to error
	p_term = KP * error * .001;
	// d term is proportional to derivative of error
	// d(error) = (e(t1)-e(t2))/(t2-t1), derivative expression
	d_term = KD * (error - prev_error);
	correction = p_term + d_term;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	// clamp maximum and minimum voltages
	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;
	prev_error = error;
}

int move_forward(){
	do {
		moveLeftMotor(1, mouseSpeedL);
		moveRightMotor(1, mouseSpeedR);
		corridor_correction();
	} while (dis_FL > 50 || dis_FR > 50);
	moveRightMotor(1, 0);
	moveLeftMotor(1, 0);

	return 0;
}

void turn180() {
	turn(1);
	turn(1);
}
