#include "../Inc/arm.h"
#include "math.h"
#include "UART_servo.h"
#include "stm32f4xx_hal.h"
#include "../../motor_ctrl/Inc/motor_monitor.hpp"
#include <stdint.h>
#include <stdbool.h>

extern UART_HandleTypeDef huart3;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim12;


// UART_servo 物件
UART_servo servo1(1, 2000, huart3);
UART_servo servo2(3, 2000, huart3);
UART_servo servo3(4, 2000, huart3);
int pos1 = 110, pos2 = 101, pos3 = 30;
int gripper_open = 60, gripper_close = 25;
int camera_front = 25, camera_down = 118;

#define CASCADE_STARTHIGHT 250.0f
float cascade_height = CASCADE_STARTHIGHT; //cascade起始高度

#define MAX_PWM 1000
#define MIN_PWM 300
#define ENCODER_RESOLUTION 256  // Encoder 脈衝數
#define REDUCTION_RATIO 24.0f  // 減速比
#define DELAY_MS 1             // 10ms 更新一次

int16_t enc_count;
int16_t count;
int pwm_value = 0;
float target_distance = 0;
float distance = 0.0f;   // 累積距離
int check=0;
float kp = 0.001, ki = 0;
float integral =0.0;
int microswitch_touched = 0;

float error, u;
int a=0, b=0, c=0, d=113;

int arm_status = 1;
int all_status =0;
static uint32_t last_command_time = 0;

void arm_reset(void) {
	// 手臂重置邏輯
	HAL_Init();
	// 啟動 Encoder 與 PWM
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim12, TIM_CHANNEL_2);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
//	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_1);

	servo1.update_pos(pos1+70);
	servo2.update_pos(pos2+100);
	servo3.update_pos(gripper_close);

	servo1.run();
	servo2.run();
	servo3.run();
}

//void cascade_monitor(float target_height) {
//	while(1) {
//
//		//如果碰到微動 設為起始高度 停止馬達
//		if(cascade_height==250 && target_height < 250 && check ==1){
//			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 0); // 停止馬達
//			break;
//		}
//		if(microswitch_touched==1 && check ==0){
//			cascade_height = CASCADE_STARTHIGHT;
//			target_height = CASCADE_STARTHIGHT;
//
//			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 0); // 停止馬達
//			check++;
//			break;
//		}
//		if(microswitch_touched==0 && check ==1) check--;
//
//		// 讀取 encoder
//		enc_count = __HAL_TIM_GET_COUNTER(&htim1);
//		enc_count = -enc_count;
//		__HAL_TIM_SET_COUNTER(&htim1, 0);  // 歸零
//
//		// 計算累積距離
//		cascade_height += (float)enc_count / (4.0f * ENCODER_RESOLUTION * REDUCTION_RATIO)* 3.14 * 35;
//
//		// 判斷是否到點
//		error = target_height - cascade_height;
//		if(fabs(error) <= 0.1) {
//			__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, 0); // 到點停
//			break;
//		}
//		float bound = 0.0;
//		if(ki != 0.0) bound = 1.0 / ki;
//		integral += error * DELAY_MS / 1000.0;
//		if(integral > bound) integral = bound;
//		else if(integral < -bound) integral = -bound;
//
//		u = kp * error + ki * integral;
//		if(u > 1) u = 1;
//		else if(u < -1 )u = -1;
//
//		if(u<0){ //TEST馬達正反轉
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_SET);
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//		}
//		else{
//			HAL_GPIO_WritePin(GPIOA, GPIO_PIN_12, GPIO_PIN_RESET);
//			HAL_GPIO_WritePin(GPIOC, GPIO_PIN_4, GPIO_PIN_RESET);
//		}
//
//		// PWM 越接近越慢
//		pwm_value = (int)(MAX_PWM * fabs(u));
//		if(pwm_value < MIN_PWM) pwm_value = MIN_PWM;
//		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_2, pwm_value);
//
//		HAL_Delay(DELAY_MS); // 10ms 更新一次
//		}
//}

void menu_camera(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250);
	if(cascade_complete()){
		servo1.update_pos(pos1+70);
		servo2.update_pos(pos2+70);
		servo3.update_pos(gripper_open);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 600+10*camera_front);
		servo1.run();
		servo2.run();
		servo3.run();
		if(current_time-last_command_time>2000){
			all_status = 1;
			arm_status = 1;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void menu_arm_1(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250+324);
	if(cascade_complete()){
		servo1.update_pos(pos1-18);
		servo2.update_pos(pos2-18);
		servo3.update_pos(gripper_open);

		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 600+10*camera_front);
		servo1.run();
		servo2.run();
		servo3.run();
		if(current_time-last_command_time>2000){
			arm_status = 2;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void menu_arm_2(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250+324);
	if(cascade_complete()){
		servo3.update_pos(gripper_close);
		servo3.run();
		if(current_time-last_command_time>2000){
			all_status = 1;
			arm_status = 1;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void table_camera(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250+29);
	if(cascade_complete()){
		servo1.update_pos(pos1-19); //35
		servo2.update_pos(pos2-19); //90
		servo3.update_pos(gripper_close);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 600+10*camera_down);
		servo1.run();
		servo2.run();
		servo3.run();
		if(current_time-last_command_time>2000){
			all_status = 1;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void table_arm_1(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250+73);
	if(cascade_complete()){
		servo1.update_pos(pos1-56);
		servo2.update_pos(pos2-56);
		servo3.update_pos(gripper_close);
		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 600+10*camera_front);
		servo1.run();
		servo2.run();
		servo3.run();
		if(current_time-last_command_time>2000){
			arm_status = 2;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void table_arm_2(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250+73);
	if(cascade_complete()){
		servo3.update_pos(gripper_open);
		servo3.run();
		if(current_time-last_command_time>2000){
			arm_status = 3;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void table_arm_3(void) {
	uint32_t current_time = HAL_GetTick();
	cascade_monitor(250);
	if(cascade_complete()){
		servo1.update_pos(pos1+70);
		servo2.update_pos(pos2+100);
		servo3.update_pos(gripper_open);
		servo1.run();
		servo2.run();
		servo3.run();
		if(current_time-last_command_time>2000){
			all_status = 1;
			arm_status = 1;
			last_command_time = current_time;
		}
	}
	else{
		servo1.run();
		servo2.run();
		servo3.run();
		last_command_time = current_time;
	}
}

void arm_test(void) {
	cascade_monitor(cascade_height);
//	if(cascade_complete()){
//		servo1.update_pos(pos1+a);
//		servo2.update_pos(pos2+b);
//		servo3.update_pos(gripper_open);
//		__HAL_TIM_SET_COMPARE(&htim5, TIM_CHANNEL_1, 600+10*c);
//		servo1.run();
//		servo2.run();
//		servo3.run();
//	}
//	else{
//		servo1.run();
//		servo2.run();
//		servo3.run();
//	}
}

void arm_mission(int code) {
	// 根據 code 執行不同的手臂任務
	switch(code) {
		case 1:
			menu_camera();
			break;
		case 2:
			switch(arm_status){
				case 1:
				menu_arm_1();
				case 2:
				menu_arm_2();
			}
			break;
		case 3:
			table_camera();
			break;
		case 4:
			switch(arm_status){
				case 1:
				table_arm_1();
				case 2:
				table_arm_2();
				case 3:
				table_arm_3();
			}
			break;
		default:
			// 預設情況
			break;
	}
}

bool arm_complete(){
	if(all_status)
	{
		all_status=0;
		return 1;
	}
	else
	{
		return 0;
	}
}
