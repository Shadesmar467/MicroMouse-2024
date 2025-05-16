/*
 * distance.h
 *
 *  Created on: Mar 2, 2025
 *      Author: adamhwu
 */

#ifndef INC_DISTANCE_H_
#define INC_DISTANCE_H_

#include "main.h"
#include <stdint.h>
#include "adc_manager.h"

uint16_t measure_dist(dist_t dist);

int wallDetectFront();

int wallDetectSideLeft(uint16_t valueSL);

int wallDetectSideRight(uint16_t valueSR);

#endif /* INC_DISTANCE_H_ */
