#ifndef INC_VALUES_H_
#define INC_VALUES_H_

#include <stdint.h>

/*			motors/encoders			*/
// voltages to assign to motors
#define addVoltage 0
#define biasVoltageL 180
#define biasVoltageR 180

// constants for converting encoders
#define tickConvertL 5.74125f	// every 5.74125 ticks is 1 mm
#define tickConvertR 2.90833f	//every 2.90833 ticks is 1mm
// encoder constants for turning
#define turnTicksR 37 //30 for stop-turn-stop, 20 for continuous turn
#define turnTicksL 37
#define turnTicksDiff 75
extern float encLmm, encRmm;	// dist traveled for each enc





/*			IR Sensors			*/
//re-calibrate often. center of the cell values
#define CAL_FL 2816.0
#define CAL_FR 3100.0
#define CAL_SL 3590.0
#define CAL_SR 2843.0

#define NOM_F -100.0
#define NOM_S -100.0

#define SCALE_FL -1*NOM_F/CAL_FL
#define SCALE_FR -1*NOM_F/CAL_FR
#define SCALE_SL -1*NOM_S/CAL_SL
#define SCALE_SR -1*NOM_S/CAL_SR

#define z_FL 1360
#define z_FR 788
#define z_SL 2297
#define z_SR 88

#define loc_FL 3426
#define loc_FR 2997
#define loc_SL 3544
#define loc_SR 2734


// normalized IR readings
extern int dis_FL;
extern int dis_FR;
extern int dis_SL;
extern int dis_SR;

// walldetect values
#define DETECT_FL 110.0
#define DETECT_FR 110.0
#define DETECT_SL 70.0
#define DETECT_SR 100.0





/* 			PID Values			*/
// IR sensor PID
#define KP_l 5 // calibrate
#define KD_l 20 // calibrate
#define KI_l 0.0
extern float prev_error_l;
extern float error_integral;

#define KP_r 1.7 // calibrate
#define KD_r 20 // calibrate
extern float prev_error_r;

#define CRUISE_SPEED 230
#define CLK_PERIOD .001

// encoder PID
#define eKP 1000 //currently untuned
#define eKD 0
extern float prev_encoder_error;
extern float currentEncDist;
extern float enclIdeal;
extern float encrIdeal;

// state
extern int rotating;

// current mouse speed
extern int mouseSpeedR;
extern int mouseSpeedL;

extern int debug1;
extern int debug2;
extern int debug3;
extern int debug4;
extern int debug5;
extern int debug6;
extern int debug7;
extern int debug8;
extern int debug9;


#endif /* INC_VALUES_H_ */
