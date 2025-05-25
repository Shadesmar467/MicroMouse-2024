/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <math.h>

#include "main.h"
#include "motors.h"
#include "values.h"
#include "distance.h"
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
		if (dis_FL < 2 || dis_FR < 2) {
			break;
		}
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
		PID();
	}

	moveRightMotor(!direction, 80);
	moveLeftMotor(!direction, 80);
	return 0;
}

void turn(int rightDir) {
	HAL_Delay(200);
	rotating = 1;

	float encLmmStart = encLmm;
	float encRmmStart = encRmm;

	while (fabsf((encLmm-encLmmStart) - (encRmm-encRmmStart)) < turnTicksDiff) {
		moveLeftMotor(rightDir, biasVoltageL + 80);
		moveRightMotor(!rightDir, biasVoltageR + 80);
	}
	moveLeftMotor(!rightDir, 80);
	moveRightMotor(rightDir, 80);
	rotating = 0;
	HAL_Delay(200);
}

void turn180() {
		turn(1);
		turn(1);
		//backAlign();
}
