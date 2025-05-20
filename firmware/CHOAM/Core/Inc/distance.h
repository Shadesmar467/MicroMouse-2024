#ifndef INC_DISTANCE_H_
#define INC_DISTANCE_H_

#include "main.h"
#include <stdint.h>
#include "adc_manager.h"

uint16_t measure_dist(dist_t dist);

int wallDetectFront();

int wallDetectLeft();

int wallDetectRight();

#endif /* INC_DISTANCE_H_ */
