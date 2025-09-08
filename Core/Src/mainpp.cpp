/*
 * mainpp.cpp
 *
 *  Created on: Aug 20, 2025
 *      Author: cathy
 */


#include "mainpp.h"
#include "arm.h"
#include "UART_servo.h"
#include "stm32f4xx_hal.h"

float goal_height = 250;


void main_function(){
	arm_reset();
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	while(1){
//		cascade_go(goal_height);
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 600+10*a);
//
//		arm_test();
//		menu_camera();
//		HAL_Delay(3000);
//		menu_arm();
//		table_camera();
//		HAL_Delay(3000);
//		table_arm();
	}
}



