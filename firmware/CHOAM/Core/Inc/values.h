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
extern int dis_FL;
extern int dis_FR;
extern int dis_SL;
extern int dis_SR;

//re-calibrate often. center of the cell values
#define CAL_FL 3321.0
#define CAL_FR 3461.0
#define CAL_SL 3600.0
#define CAL_SR 3217.0

#define NOM_F 100.0
#define NOM_S 100.0

#define SCALE_FL -1*NOM_F/CAL_FL
#define SCALE_FR -1*NOM_F/CAL_FR
#define SCALE_SL -1*NOM_S/CAL_SL
#define SCALE_SR -1*NOM_S/CAL_SR


// movement values
#define KP 1.1f // calibrate, currently arbitrary
#define KD 1.2f // calibrate, currently arbitrary
extern float prev_error;

// constant tick values for desired cushion
#define  dis_FL_30mm 3485
#define  dis_FR_30mm 3640
#define  dis_SL_30mm 3720
#define  dis_SR_30mm 3570

extern int mouseSpeedR;
extern int mouseSpeedL;

#endif /* INC_VALUES_H_ */
