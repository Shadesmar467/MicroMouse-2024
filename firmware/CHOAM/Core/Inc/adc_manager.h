/*
 * adc_manager.h
 *
 *  Created on: Mar 2, 2025
 *      Author: adamhwu
 */

#pragma once

#ifndef INC_ADC_MANAGER_H_
#define INC_ADC_MANAGER_H_

#include "main.h"

extern ADC_HandleTypeDef hadc1;

void ADC1_Select_CH4(void);
void ADC1_Select_CH5(void);
void ADC1_Select_CH8(void);
void ADC1_Select_CH9(void);

#endif /* INC_ADC_MANAGER_H_ */
