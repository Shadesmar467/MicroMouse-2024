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
	error = dis_SL - 28;

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
	float lnew, rnew, error, p_term, d_term, i_term, correction;
	int max_correct, min_correct;
	error = dis_SL - dis_SR;
	error_integral += error;

	// p term is proportional to error
	p_term = KP_l * error * .01;
	// d term is proportional to derivative of error
	// d(error) = (e(t1)-e(t2))/(t2-t1), derivative expression
	d_term = KD_l * (error - prev_error_l);
	i_term = KI_l * error_integral;
	correction = p_term + d_term + i_term;

	lnew = mouseSpeedL - correction;
	rnew = mouseSpeedR + correction;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	// clamp maximum and minimum voltages
	if (lnew < min_correct){
		mouseSpeedL = min_correct;
	}
	else if (lnew > max_correct){
		mouseSpeedL = max_correct;
	}
	else {
		mouseSpeedL = lnew;
	}

	if (rnew < min_correct){
		mouseSpeedR = min_correct;
	}
	else if (rnew > max_correct){
		mouseSpeedR = max_correct;
	}
	else {
		mouseSpeedR = rnew;
	}

	prev_error_l = error;
}

void encoder_PID(){
	float lnew, rnew;
	int max_correct, min_correct;
	//ideally difference should be zero for the motors to both travel the same distance
	float errorl = encLmm - enclIdeal;
	float errorr = encRmm - encrIdeal;

	float correctionl = eKP*errorl;
	float correctionr = eKP*errorr;

	lnew = mouseSpeedL + correctionl;
	rnew = mouseSpeedR + correctionr;

	max_correct = CRUISE_SPEED + 30;
	min_correct = CRUISE_SPEED - 30;

	if (lnew < min_correct){
		mouseSpeedL = min_correct;
	}
	else if (lnew > max_correct){
		mouseSpeedL = max_correct;
	}
	else {
		mouseSpeedL = lnew;
	}

	if (rnew < min_correct){
		mouseSpeedR = min_correct;
	}
	else if (rnew > max_correct){
		mouseSpeedR = max_correct;
	}
	else {
		mouseSpeedR = rnew;
	}
}

void PID(){
	if (wallDetectLeft() && wallDetectRight())
		IR_PID();

//	encoder_PID();
}
