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
#include "distance.h"

void moveLeftMotor(int direction, int speed) {
	SetLMotorDirection(direction);
	TIM2->CCR4 = fabsf(speed);
}

void moveRightMotor(int direction, int speed) {
	SetRMotorDirection(direction);
	TIM2->CCR3 = fabsf(speed);
}

void stopMotors() {
	moveRightMotor(0, 0);
	moveLeftMotor(0, 0);
}

int move_dist(float dist, uint16_t* valueFL, uint16_t* valueFR) {
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

		if (wallDetectFront(dis_FL, dis_FR)) {
			break;
		}
		continue;
	}

	moveRightMotor(direction, 0);
	moveLeftMotor(direction, 0);
	return 0;
}

void corridor_correction() {

	// PSUEDO CODE

	// get ERROR: difference in IR sensors
	// get DIFF: current - prev errors
	// set prev to current error
	// get PD: Kp * ERROR + Kd * DIFF

	// conversion in output to rotational adjustment (constants or later conversion)

	// set left speed to current speed plus rotational adjustment // +/- figure out
	// set right speed to current speed minues rotational adjustment

	// set left voltage by converting left speed to voltage
	// set right voltage by converting right speed to voltage

	// set left motor to left voltage
	// set right motor to right voltage

	float ir_sl = measure_dist(DIST_SL) * SCALE_SL; // get normalized ir value
	float ir_sr = measure_dist(DIST_SR) * SCALE_SR; // get normalized ir value
	float error = ir_sl - ir_sr;  // get error, or difference between ir values

	float diff = error - prev_error; // get difference from current and previous error

	prev_error = error; // set previous error to current

	float pd = KP * error + KD * diff; // pd output

	float percent_error = pd / 200; // 200 is the max error between IR sensors, adjust
	float rot_change = percent_error * 10; // 10 * 2 is the max motor difference to rotate mouse, adjust

	float left_volts = mouseSpeedL - rot_change; // changing current volts to rotate
	float right_volts = mouseSpeedR + rot_change; // changing current volts to rotate

	moveLeftMotor(1, left_volts); // setting motor speeds to adjusted speed
	moveRightMotor(1, right_volts); // setting motor speeds to adjusted speed
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

void turn180() {
	turn(1);
	turn(1);
}
