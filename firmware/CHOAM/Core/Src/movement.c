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

int move_dist(float dist) {
	int startencL = encLmm;
	int startencR = encRmm;
	int direction = (dist > 0) ? 1 : 0;

	//int overshoot_dist = 10;

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
