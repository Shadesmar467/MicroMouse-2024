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

int move_dist(float dist, uint16_t* valueFL, uint16_t* valueFR);

void turn180();

void frontStraighten();

void turn(int rightDir);

#endif /* INC_MOVEMENT_H_ */
