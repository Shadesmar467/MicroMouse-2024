#include <stdint.h>
#include "main.h"
#include "motors.h"

void LReverse(){
	//ML Backwards HIGH
	HAL_GPIO_WritePin(GPIOB, 14, 1);
	//ML Forward LOW
	HAL_GPIO_WritePin(GPIOA, 8, 0);
}

void LForward(){
	//ML Backwards LOW
	HAL_GPIO_WritePin(GPIOB, 14, 0);
	//ML Forward HIGH
	HAL_GPIO_WritePin(GPIOA, 8, 1);
}

void RReverse(){
	//ML Backwards HIGH
	HAL_GPIO_WritePin(GPIOB, 15, 1);
	//ML Forward LOW
	HAL_GPIO_WritePin(GPIOB, 13, 0);
}

void RForward(){
	//ML Backwards LOW
	HAL_GPIO_WritePin(GPIOB, 15, 0);
	//ML Forward HIGH
	HAL_GPIO_WritePin(GPIOB, 13, 1);
}

void mDrive(){
	RForward();
	LForward();
}

void mReverse(){
	RReverse();
	LReverse();
}

