#include <stdint.h>
#include "main.h"
#include "motors.h"

void SetLMotorDirection(int forward){
	if (forward){
		/*
		//ML Backwards LOW
		HAL_GPIO_WritePin(GPIOB, ML_BWD_Pin, GPIO_PIN_RESET);
		//ML Forward HIGH
		HAL_GPIO_WritePin(GPIOA, ML_FWD_Pin, GPIO_PIN_SET);
		*/

		//ML Backwards LOW
		HAL_GPIO_WritePin(GPIOB, 14, GPIO_PIN_RESET);
		//ML Forward HIGH
		HAL_GPIO_WritePin(GPIOA, 8, GPIO_PIN_SET);
	} else {
		//ML Backwards HIGH
		HAL_GPIO_WritePin(GPIOB, ML_BWD_Pin, GPIO_PIN_SET);
		//ML Forward LOW
		HAL_GPIO_WritePin(GPIOA, ML_FWD_Pin, GPIO_PIN_RESET);
	}
}

void SetRMotorDirection(int forward){
	if (forward){
		//MR Backwards LOW
		HAL_GPIO_WritePin(GPIOB, MR_BWD_Pin, GPIO_PIN_RESET);
		//MR Forward HIGH
		HAL_GPIO_WritePin(GPIOB, MR_FWD_Pin, GPIO_PIN_SET);
	} else {
		//MR Backwards HIGH
		HAL_GPIO_WritePin(GPIOB, MR_BWD_Pin, GPIO_PIN_SET);
		//MR Forward LOW
		HAL_GPIO_WritePin(GPIOB, MR_FWD_Pin, GPIO_PIN_RESET);
	}
}

