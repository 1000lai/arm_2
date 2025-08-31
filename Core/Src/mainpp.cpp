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
//
//extern UART_HandleTypeDef huart3;
//
//UART_servo servo1(1,2000,huart3);
//UART_servo servo2(3,2000,huart3);
//UART_servo servo3(4,2000,huart3);
//UART_servo servo4(5,2000,huart3);
//extern TIM_HandleTypeDef htim2;
//int pos1 = 35, pos2 = 28, pos3 = 30, a = 0; //pos4不能小於10
//int pos_1 = 0, pos_2 = 0, pos_3 = 0;
//int gripper_open = 60, gripper_close = 25;
//int camera_front = 25, camera_down = 113;
//extern TIM_HandleTypeDef htim2;
//int a=25;
float goal_height = 146;


void main_function(){
	arm_reset();
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	while(1){
//
//		__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 600+10*a);
//
//		arm_test();
//		menu_camera();
//		menu_arm();
		table_camera();
		HAL_Delay(3000);
		table_arm();
	}
}



