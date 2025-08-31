/*
 * arm.cpp
 *
 *  Created on: Aug 27, 2025
 *      Author: cathy
 */

#include "mainpp.h"
#include "arm.h"
#include "math.h"
#include "UART_servo.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart3;

UART_servo servo1(1,2000,huart3);
UART_servo servo2(3,2000,huart3);
UART_servo servo3(4,2000,huart3);
UART_servo servo4(5,2000,huart3);
extern TIM_HandleTypeDef htim2;
int pos1 = 35, pos2 = 28, pos3 = 30;
int pos_1 = 0, pos_2 = 0, pos_3 = 0;
int gripper_open = 60, gripper_close = 25;
int camera_front = 30, camera_down = 113;

#define CASCADE_STARTHIGHT 146.0f
float cascade_height = CASCADE_STARTHIGHT; //cascade起始高度

#define MAX_PWM 800
#define MIN_PWM 300
#define ENCODER_RESOLUTION 100  // Encoder 脈衝數
#define REDUCTION_RATIO 64.0f  // 減速比
#define DELAY_MS 1             // 10ms 更新一次

int16_t enc_count;
int16_t count;
int pwm_value = 0;
float target_distance = 0;
float distance = 0.0f;   // 累積距離
uint8_t reached = 0;
float kp = 0.001, ki = 0;
float integral =0.0;
int microswitch_touched = 0;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim8;
float error, u;
int a=0, b=0, c=0;

void arm_reset(){
	HAL_Init();

	// 啟動 Encoder 與 PWM
	HAL_TIM_Encoder_Start(&htim1, TIM_CHANNEL_ALL);
	HAL_TIM_PWM_Start(&htim8, TIM_CHANNEL_3);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_12, GPIO_PIN_SET);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_1);

	servo1.update_pos(pos1+70);
	servo2.update_pos(pos2+145);
	servo3.update_pos(pos3+20);
	servo4.update_pos(gripper_close);

	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
}

void cascade_go(float target_height){

	while(1) {

		//如果碰到微動 設為起始高度 停止馬達
		if(microswitch_touched==1){
			cascade_height = CASCADE_STARTHIGHT;
			target_height = CASCADE_STARTHIGHT;
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0); // 停止馬達
			break;
		}

		// 讀取 encoder
		enc_count = __HAL_TIM_GET_COUNTER(&htim1);
		enc_count = -enc_count;
		__HAL_TIM_SET_COUNTER(&htim1, 0);  // 歸零

		// 計算累積距離
		cascade_height += (float)enc_count / (4.0f * ENCODER_RESOLUTION * REDUCTION_RATIO)* 3.14 * 35;

		// 判斷是否到點
		error = target_height - cascade_height;
		if(fabs(error) <= 0.1) {
			__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, 0); // 到點停
			break;
		}
		float bound = 0.0;
		if(ki != 0.0) bound = 1.0 / ki;
		integral += error * DELAY_MS / 1000.0;
		if(integral > bound) integral = bound;
		else if(integral < -bound) integral = -bound;

		u = kp * error + ki * integral;
		if(u > 1) u = 1;
		else if(u < -1 )u = -1;

		if(u<0)HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_SET);
		else HAL_GPIO_WritePin(GPIOB, GPIO_PIN_13, GPIO_PIN_RESET);

		// PWM 越接近越慢
		pwm_value = (int)(MAX_PWM * fabs(u));
		if(pwm_value < MIN_PWM) pwm_value = MIN_PWM;
		__HAL_TIM_SET_COMPARE(&htim8, TIM_CHANNEL_3, pwm_value);

		HAL_Delay(DELAY_MS); // 10ms 更新一次
		}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	if(GPIO_Pin == GPIO_PIN_7)
	{
		if(HAL_GPIO_ReadPin(GPIOC,GPIO_PIN_7) == GPIO_PIN_RESET){
			cascade_height = CASCADE_STARTHIGHT;
			microswitch_touched=1;
		}
		else microswitch_touched=0;
	}

}

void menu_camera(){

	servo1.update_pos(pos1+70);
	servo2.update_pos(pos2+140);
	servo3.update_pos(pos3+68);
	servo4.update_pos(gripper_open);

	cascade_go(250);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 600+10*camera_front);
	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
	HAL_Delay(3000);
}

void menu_arm(){
	servo1.update_pos(pos1+15);
	servo2.update_pos(pos2+70);
	servo3.update_pos(pos3+50);
	servo4.update_pos(gripper_open);

	//空中打開
	cascade_go(300);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 600+10*camera_front);
	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
	HAL_Delay(3000);

	//桌面打開
	cascade_go(200);
	HAL_Delay(3000);

	//桌面夾起
	servo4.update_pos(gripper_close);
	servo4.run();
	HAL_Delay(3000);
}

void table_camera(){
	servo1.update_pos(pos1+27); //35
	servo2.update_pos(pos2+23); //90
	servo3.update_pos(pos3-15); //55
	servo4.update_pos(gripper_close);

	cascade_go(146);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 600+10*camera_down);
	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
	HAL_Delay(3000);
}
void table_arm(){
	servo1.update_pos(pos1-3);
	servo2.update_pos(pos2+75);
	servo3.update_pos(pos3+85);
	servo4.update_pos(gripper_close);

	//桌面夾起
	cascade_go(146);
	__HAL_TIM_SET_COMPARE(&htim2, TIM_CHANNEL_1, 600+10*camera_front);
	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
	HAL_Delay(3000);

	//桌面打開
	servo4.update_pos(gripper_open);
	servo4.run();
	HAL_Delay(3000);

	//手播收回
	servo1.update_pos(pos1+70);
	servo2.update_pos(pos2+145);
	servo3.update_pos(pos3+20);
	servo4.update_pos(gripper_open);
	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
	HAL_Delay(3000);
}

void arm_test(){
	servo1.update_pos(pos1+a);
	servo2.update_pos(pos2+b);
	servo3.update_pos(pos3+c);
	servo4.update_pos(gripper_close);
	servo1.run();
	servo2.run();
	servo3.run();
	servo4.run();
}


