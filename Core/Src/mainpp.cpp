/*
 * mainpp.cpp
 *
 *  Created on: Aug 20, 2025
 *      Author: cathy
 */


#include "arm_2.h"
#include "mainpp.h"
#include "UART_servo.h"
#include "stm32f4xx_hal.h"


#include "arm/Inc/arm.h"
#include "motor_ctrl/Inc/motor_ctrl.hpp"
#include "motor_ctrl/Inc/motor_monitor.hpp"

float goal_height = 250;
float sp = 0;
int sec = 0;

int code = 0;

extern MotorController Motor_cas;
extern TIM_HandleTypeDef htim4;

void main_function(){

	arm_reset();
	HAL_TIM_Base_Start_IT(&htim4);
	motor_init();
//	arm_test();
//	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	while(1){
//		Motor_cas.setSpeed(sp);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
//		HAL_Delay(2000);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//		HAL_Delay(1500);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//		HAL_Delay(2000);
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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  /* USER CODE BEGIN Callback 0 */
	if (htim->Instance == TIM4)
	{
		sec++;
//		motor_monitor();
		cascade_monitor(300);

//		arm_test();
//		__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_2, (uint16_t)300);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_RESET);

//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);
//		HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//		__HAL_TIM_SET_COMPARE(&htim12,TIM_CHANNEL_2,pulse);

		arm_mission(code);

//		if(arm_complete())
//		{
//			arm_pub_cb(1);
//		}
//		else
//		{
//			if(code>0){
//				arm_mission(code);
//			}
//		}
	}
  /* USER CODE END Callback 0 */

  /* USER CODE BEGIN Callback 1 */
//
  /* USER CODE END Callback 1 */
}

