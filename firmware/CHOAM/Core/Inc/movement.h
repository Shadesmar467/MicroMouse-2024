#ifndef INC_MOVEMENT_H_
#define INC_MOVEMENT_H_

void moveLeftMotor(int direction, int speed);

void moveRightMotor(int direction, int speed);

void stopMotors();

void backAlign();

int move_dist(float dist);

void turn180();

void corridor_correction_IR();

int move_forward();

void turn(int rightDir);

#endif /* INC_MOVEMENT_H_ */
