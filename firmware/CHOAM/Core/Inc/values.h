/*
 * values.h
 *
 *  Created on: Apr 24, 2025
 *      Author: adamhwu
 */

#ifndef INC_VALUES_H_
#define INC_VALUES_H_

#include <stdint.h>

// motors/encoders //

// voltages to assign to motors
#define addVoltage 100
#define biasVoltageL 170
#define biasVoltageR 170

// constants for converting encoders
#define tickConvertL 5.74125f	// every 5.74125 ticks is 1 mm
#define tickConvertR 2.90833f	//every 2.90833 ticks is 1mm
// encoder constants for turning
#define turnTicksR 30
#define turnTicksL 30
extern float encLmm, encRmm;	// dist traveled for each enc

// IR Sensors
extern uint16_t dis_FL;
extern uint16_t dis_FR;
extern uint16_t dis_SL;
extern uint16_t dis_SR;

const int NOM_F = 100;  // range of values for IR front sensors
const int NOM_S = 100;  // range of values for IR side sensors

const int CAL_FL = 3321; //re-calibrate per location
const int CAL_FR = 3461;
const int CAL_SL = 3600;
const int CAL_SR = 3217;

extern int SCALE_FL;
extern int SCALE_FR;
extern int SCALE_SL;
extern int SCALE_SR;

// movement values
const float KP = 1.1; // calibrate, currently arbitrary
const float KD = 1.2; // calibrate, currently arbitrary
extern float prev_error;

// constant tick values for desired cushion
#define  dis_FL_30mm 3485
#define  dis_FR_30mm 3640
#define  dis_SL_30mm 3720
#define  dis_SR_30mm 3570

extern int mouseSpeedR;
extern int mouseSpeedL;

#endif /* INC_VALUES_H_ */
