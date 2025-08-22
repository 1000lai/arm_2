/*
 * mainpp.cpp
 *
 *  Created on: Aug 20, 2025
 *      Author: cathy
 */


#include "mainpp.h"
#include "UART_servo.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart3;

UART_servo servo1(1,1000,huart3);
UART_servo servo2(3,1000,huart3);
UART_servo servo3(4,1000,huart3);
UART_servo servo4(5,1000,huart3);
int pos1 = 0, pos2 = 0, pos3 = 0, pos4 = 30, a = 0; //pos4不能小於10
void main_function(){
	while(1){
		servo1.update_pos(pos1);
		servo2.update_pos(pos2);
		servo3.update_pos(pos3);
		servo4.update_pos(pos4);

		servo1.run();
		servo2.run();
		servo3.run();
		servo4.run();
		//a++;
//			if(a>1000){
//				a=0;
//				pos++;
//			}
	}
}
