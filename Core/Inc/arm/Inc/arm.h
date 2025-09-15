#ifndef INC_ARM_H_
#define INC_ARM_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif

// C 函數宣告
extern float cascade_height;
extern int arm_status;
extern int all_status;

void arm_reset(void);
void cascade_go(float target_height);
void menu_camera(void);
void menu_arm(void);
void table_camera(void);
void table_arm(void);
void arm_test(void);
void arm_mission(int code);
bool arm_complete();

#ifdef __cplusplus
}

// C++ 標頭檔和類別定義
#include "UART_servo.h"

#endif /* __cplusplus */

#endif /* INC_ARM_H_ */
