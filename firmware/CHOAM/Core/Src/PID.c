/*
 * PID.c
 *
 *  Created on: May 25, 2025
 *      Author: adamhwu
 */

#include "PID.h"
#include "values.h"
#include "distance.h"

void leftWallPID(){
	float lnew, rnew, error, p_term, d_term, correction;
	int max_correct, min_correct;
	error = dis_SL - 25;

	p_term = KP_l * error * .001;

	d_term = KD_l * (error - prev_error_l);
	correction = p_term + d_term;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	// clamp maximum and minimum voltages
	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;
	prev_error_l = error;
}

void rightWallPID(){
	float lnew, rnew, error, p_term, d_term, correction;
	int max_correct, min_correct;
	error = dis_SR - 20;

	p_term = KP_r * error * .001;

	d_term = KD_r * (error - prev_error_r);
	correction = p_term + d_term;

	lnew = mouseSpeedL + correction;
	rnew = mouseSpeedR - correction;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	// clamp maximum and minimum voltages
	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;
	prev_error_r = error;
}

void IR_PID() {
	//if (wallDetectLeft() && rotating == 0){
		//leftWallPID();
	//}
	 if (wallDetectRight() && rotating == 0) {
		rightWallPID();
	}
}

void encoder_PID(){
	float lnew, rnew;
	int max_correct, min_correct;
	//ideally difference should be zero for the motors to both travel the same distance
	float error = encLmm - encRmm;
	float d = error - prev_encoder_error;
	float correction = eKP*error + eKD*d;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	mouseSpeedL = (lnew < max_correct && lnew > min_correct) ? lnew : mouseSpeedL;
	mouseSpeedR = (rnew < max_correct && rnew > min_correct) ? rnew : mouseSpeedR;

	prev_encoder_error = error;
}

void PID(){
	IR_PID();
}
