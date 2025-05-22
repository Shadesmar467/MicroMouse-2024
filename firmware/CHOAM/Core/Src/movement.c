/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "main.h"
#include "motors.h"
#include "values.h"
#include "distance.h"
#include <math.h>
#include "movement.h"

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

void backAlign() {
	float encLBack = encLmm - 30;
	float encRBack = encRmm - 30;

	while ((encRmm > encRBack) && (encLmm > encLBack)) {
		moveRightMotor(0, mouseSpeedR);
		moveLeftMotor(0, mouseSpeedL);
	}
}

int move_dist(float dist) {
	float startencL = encLmm;
	float startencR = encRmm;
	int direction = (dist > 0) ? 1 : 0;
	mouseSpeedL = CRUISE_SPEED;
	mouseSpeedR = CRUISE_SPEED;

	while (encRmm < dist+startencR && encLmm < dist+startencL){
		// Right motor profile
		if (encRmm-startencR < dist * .6){
			moveRightMotor(direction, mouseSpeedR);
		}
		else {
			moveRightMotor(direction, CRUISE_SPEED-50);
		}

		// Left motor profile
		if (encLmm-startencL < dist * .6) {
			moveLeftMotor(direction, mouseSpeedL);
		}
		else {
			moveLeftMotor(direction , CRUISE_SPEED-50);
		}

		if (wallDetectLeft() && wallDetectRight()) {
//				corridor_correction_IR();
		}

		continue;
	}

	moveRightMotor(!direction, 120);
	moveLeftMotor(!direction, 80);
	return 0;
}

void turn(int rightDir) {
	HAL_Delay(500);
	rotating = true;
	float targetL = (rightDir) ? encLmm + turnTicksL : encLmm - turnTicksL;
	float targetR = (rightDir) ? encRmm - turnTicksR : encRmm + turnTicksR;

	if (rightDir){
		while ((encRmm > targetR) || (encLmm < targetL)) {
				moveLeftMotor(1, biasVoltageL + 50);
				moveRightMotor(0, biasVoltageR + 50);
		}
		moveRightMotor(1,80);
		moveLeftMotor(0,80);

	}

	else {
		while ((encRmm < targetR) || (encLmm > targetL)) {
				moveLeftMotor(0, biasVoltageL + 50);
				moveRightMotor(1, biasVoltageR + 50);
		}
		moveLeftMotor(1,80);
		moveRightMotor(0,80);
	}
	rotating = false;
	HAL_Delay(500);
}

void corridor_correction_IR() {
	float lnew, rnew, error, p_term, d_term, correction;
	int max_correct, min_correct;
	// error is high if closer to right, low if close to left
	error = dis_SL - dis_SR;
	// p term is proportional to error
	p_term = KP * error * .001;
	// d term is proportional to derivative of error
	// d(error) = (e(t1)-e(t2))/(t2-t1), derivative expression
	d_term = KD * (error - prev_error_b);
	correction = p_term + d_term;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	// clamp maximum and minimum voltages
	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;
	prev_error_b = error;
}

void left_corridor_correction_IR() {
	float lnew, rnew, error, p_term, d_term, correction;
	int max_correct, min_correct;
	// error is high if closer to right, low if close to left
	error = dis_SL - 25; // TUNE 25 IS CENTER?
	// p term is proportional to error
	p_term = KP * error * .001;
	// d term is proportional to derivative of error
	// d(error) = (e(t1)-e(t2))/(t2-t1), derivative expression
	d_term = KD * (error - prev_error_l);
	correction = p_term + d_term;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED + 30; // TUNE FLIP
	min_correct = CRUISE_SPEED - 30;

	// clamp maximum and minimum voltages
	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;
	prev_error_l = error;
}

void right_corridor_correction_IR() {
	float lnew, rnew, error, p_term, d_term, correction;
	int max_correct, min_correct;
	// error is high if closer to right, low if close to left
	error = dis_SR - 25; // TUNE 25 IS CENTER??
	// p term is proportional to error
	p_term = KP * error * .001;
	// d term is proportional to derivative of error
	// d(error) = (e(t1)-e(t2))/(t2-t1), derivative expression
	d_term = KD * (error - prev_error_r);
	correction = p_term + d_term;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED - 30; // TUNE FLIP
	min_correct = CRUISE_SPEED + 30;

	// clamp maximum and minimum voltages
	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;
	prev_error_r = error;
}

int move_forward(){
	do {
		moveLeftMotor(1, mouseSpeedL);
		moveRightMotor(1, mouseSpeedR);
		corridor_correction_IR();
	} while (dis_FL > 50 || dis_FR > 50);
	moveRightMotor(1, 0);
	moveLeftMotor(1, 0);

	return 0;
}

void turn180() {
		turn(1);
		turn(1);
		//backAlign();
}
