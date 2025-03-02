/*
 * distance.c
 *
 *  Created on: Mar 2, 2025
 *      Author: adamhwu
 */

uint16_t measure_dist(dist_t dist){
	GPIO_TypeDef* emitter_port;
	uint16_t emitter_pin;
	GPIO_TypeDef* receiver_port;
	uint16_t receiver_pin;

	//switch case to change emiter/receiver pair
	switch(dist) {
		case DIST_FL:
			emitter_port = EMIT_FL_GPIO_Port;
			emitter_pin = EMIT_FL_Pin;
			receiver_port = RECIV_FL_GPIO_Port;
			receiver_pin = RECIV_FL_Pin;
			ADC1_Select_CH9();
			break;
		case DIST_FR:
			emitter_port = EMIT_FR_GPIO_Port;
			emitter_pin = EMIT_FR_Pin;
			receiver_port = RECIV_FR_GPIO_Port;
			receiver_pin = RECIV_FR_Pin;
			ADC1_Select_CH4();
			break;
		default:
			break;
	}

	HAL_GPIO_WritePin(emitter_por, emitter_pin, GPIO_PIN_SET);
	HAL_Delay(5);

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	uint16_t adc_val = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Stop(&hadc1);

	HAL_GPIO_WritePin(emitter_port, emitter_pin, GPIO_PIN_RESET);

	return adc_val;
}




