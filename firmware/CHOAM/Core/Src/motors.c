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
		HAL_GPIO_WritePin(ML_BWD_GPIO_Port, ML_BWD_Pin, GPIO_PIN_RESET);
		//ML Forward HIGH
		HAL_GPIO_WritePin(ML_FWD_GPIO_Port, ML_FWD_Pin, GPIO_PIN_SET);
	} else {
		//ML Backwards HIGH
		HAL_GPIO_WritePin(ML_BWD_GPIO_Port, ML_BWD_Pin, GPIO_PIN_SET);
		//ML Forward LOW
		HAL_GPIO_WritePin(ML_FWD_GPIO_Port, ML_FWD_Pin, GPIO_PIN_RESET);
	}
}

void SetRMotorDirection(int forward){
	if (!forward){
		//MR Backwards LOW
		HAL_GPIO_WritePin(MR_BWD_GPIO_Port, MR_BWD_Pin, GPIO_PIN_RESET);
		//MR Forward HIGH
		HAL_GPIO_WritePin(MR_FWD_GPIO_Port, MR_FWD_Pin, GPIO_PIN_SET);
	} else {
		//MR Backwards HIGH
		HAL_GPIO_WritePin(MR_BWD_GPIO_Port, MR_BWD_Pin, GPIO_PIN_SET);
		//MR Forward LOW
		HAL_GPIO_WritePin(MR_FWD_GPIO_Port, MR_FWD_Pin, GPIO_PIN_RESET);
	}
}

