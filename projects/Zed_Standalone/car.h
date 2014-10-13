/*
 * car.h
 *
 *  Created on: 2014-3-31
 *      Author: Administrator
 */

#ifndef CAR_H_
#define CAR_H_

#include "motor.h"
#include "servo.h"
#include "speed.h"
#include "ultrasonic.h"
#include "OLED.h"

#define LEFT 0
#define RIGHT 1
#define ULTRASONIC_LEFT 1
#define ULTRASONIC_MIDDLE 3
#define ULTRASONIC_RIGHT 2
#define OPTICAL_LEFT 0
#define OPTICAL_LEFTMIDDLE 1
#define OPTICAL_RIGHTMIDDLE 2
#define OPTICAL_RIGHT 3
#define OPTICAL_FORWARD 4
#define FORWARD 0
#define BACKWARD 1
#define LEVEL_MIN 0x0C000
#define LEVEL_MAX 0X13000

#endif /* CAR_H_ */
