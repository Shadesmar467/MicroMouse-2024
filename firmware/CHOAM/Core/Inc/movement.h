/*
 * movement.h
 *
 *  Created on: Apr 24, 2025
 *      Author: adamhwu
 */

#ifndef INC_MOVEMENT_H_
#define INC_MOVEMENT_H_

void moveLeftMotor(int direction, int speed);

void moveRightMotor(int direction, int speed);

void stopMotors();

int move_dist(float dist);

void turn180();

void corridor_correction();

int move_forward();

void turn(int rightDir);

#endif /* INC_MOVEMENT_H_ */
