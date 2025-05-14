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

int wallDetectFront(uint16_t valueFL, uint16_t valueFR);

#endif /* INC_DISTANCE_H_ */
