/*
 * distance.c
 *
 *  Created on: Mar 2, 2025
 *      Author: adamhwu
 */

#include <stdint.h>
#include "distance.h"
#include "main.h"
#include "adc_manager.h"

uint16_t measure_dist(dist_t dist){
	GPIO_TypeDef* emitter_port;
	uint16_t emitter_pin;
	GPIO_TypeDef* receiver_port;
	uint16_t receiver_pin;

	//switch case to change emitter/receiver pair
	switch(dist) {
		case DIST_FL:
			emitter_port = EMIT_FL_GPIO_Port;
			emitter_pin = EMIT_FL_Pin;
			receiver_port = REC_FL_GPIO_Port;
			receiver_pin = REC_FL_Pin;
			ADC1_Select_CH8();
			break;
		case DIST_FR:
			emitter_port = EMIT_FR_GPIO_Port;
			emitter_pin = EMIT_FR_Pin;
			receiver_port = REC_FR_GPIO_Port;
			receiver_pin = REC_FR_Pin;
			ADC1_Select_CH4();
			break;
		case DIST_SR:
			emitter_port = EMIT_SR_GPIO_Port;
			emitter_pin = EMIT_SR_Pin;
			receiver_port = REC_SR_GPIO_Port;
			receiver_pin = REC_SR_Pin;
			ADC1_Select_CH5();
			break;
		case DIST_SL:
			emitter_port = EMIT_SL_GPIO_Port;
			emitter_pin = EMIT_SL_Pin;
			receiver_port = REC_SL_GPIO_Port;
			receiver_pin = REC_SL_Pin;
			ADC1_Select_CH9();
			break;
		default:
			break;
	}

	HAL_GPIO_WritePin(emitter_port, emitter_pin, GPIO_PIN_SET);
//	HAL_Delay(5);

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	HAL_GPIO_WritePin(emitter_port, emitter_pin, GPIO_PIN_RESET);

	return adc_val;
}




