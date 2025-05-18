/*
 * values.h
 *
 *  Created on: Apr 24, 2025
 *      Author: adamhwu
 */

#ifndef INC_VALUES_H_
#define INC_VALUES_H_

#include <stdint.h>

/*-------- motors/encoders --------*/
// voltages to assign to motors
#define addVoltage 0
#define biasVoltageL 170 // Pulse Width Modulation(PWM) signal that gets converted to a voltage
#define biasVoltageR 170 // that overcomes internal friction of the motor

// constants for converting encoders
#define tickConvertL 5.74125f // every 5.74125 ticks is 1 mm
#define tickConvertR 2.90833f //every 2.90833 ticks is 1mm
// encoder constants for turning
#define turnTicksR 30
#define turnTicksL 30
extern float encLmm, encRmm; // distance traveled for each encoder

/*----------------- IR Sensors -----------------*/
//re-calibrate often. center of the cell values
#define CAL_FL 3321.0
#define CAL_FR 3461.0
#define CAL_SL 3600.0
#define CAL_SR 3217.0

#define NOM_F 100.0 //Nominalized constant, used to convert raw to a scale of 0-100
#define NOM_S 100.0

#define SCALE_FL -1*NOM_F/CAL_FL
#define SCALE_FR -1*NOM_F/CAL_FR
#define SCALE_SL -1*NOM_S/CAL_SL
#define SCALE_SR -1*NOM_S/CAL_SR

// normalized IR readings
extern int dis_FL;
extern int dis_FR;
extern int dis_SL;
extern int dis_SR;

/*----------------- PID Values -----------------*/
#define KP 3.5 // calibrate, currently arbitrary
#define KD 20 // calibrate, currently arbitrary
#define CRUISE_SPEED 200
#define CLK_PERIOD .001
extern float prev_error;


// current mouse speed
extern int mouseSpeedR; // defined in main.c
extern int mouseSpeedL;

#endif /* INC_VALUES_H_ */
