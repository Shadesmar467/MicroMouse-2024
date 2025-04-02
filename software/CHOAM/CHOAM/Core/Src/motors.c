#include <stdint.h>
#include "main.h"
#include "motors.h"

void SetLMotorDirection(int forward){
	if (forward){
		//ML Backwards LOW
		HAL_GPIO_WritePin(GPIOB, 14, 0);
		//ML Forward HIGH
		HAL_GPIO_WritePin(GPIOA, 8, 1);
	} else {
		//ML Backwards HIGH
		HAL_GPIO_WritePin(GPIOB, 14, 1);
		//ML Forward LOW
		HAL_GPIO_WritePin(GPIOA, 8, 0);
	}
}

void SetRMotorDirection(int forward){
	if (forward){
		//MR Backwards LOW
		HAL_GPIO_WritePin(GPIOB, 15, 0);
		//MR Forward HIGH
		HAL_GPIO_WritePin(GPIOB, 13, 1);
	} else {
		//MR Backwards HIGH
		HAL_GPIO_WritePin(GPIOB, 15, 1);
		//MR Forward LOW
		HAL_GPIO_WritePin(GPIOB, 13, 0);
	}
}

