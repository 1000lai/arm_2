#include "../Inc/motor_monitor.hpp"
#include "../Inc/motor_ctrl.hpp"

extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim5;
extern TIM_HandleTypeDef htim12;

//trace :
//1    PA0   ∧右
//2    PC0    I
//3    PC1    I
//4    PC2    I
//5    PC3   ∨左
//左  PC4
//右  PC5
//switch： PA4(程式啟動)
//motor：
//           dir    pwm    enA/enB
//    FR :B12   PC6      PA8/PA9
//    FL :A12   PC7      PA1/PA5
//    BR :B14   PC8      PA6/PA7
//    BL :B15   PC9      PB6/PB7
//
MotorController Motor_cas(&htim1, &htim12, TIM_CHANNEL_2, GPIOB, GPIO_PIN_12, 1, 40, 0);
float Vgoal = 0.0;

void motor_init(){
	 Motor_cas.init(-1,-1);
}

void motor_monitor(void) {
	Motor_cas.setSpeed(Vgoal);
    // Motor_BR.setSpeed(VgoalBR);
    // Motor_FL.setSpeed(VgoalFL);
    // Motor_BL.setSpeed(VgoalBL);
//    test = Motor_BR.getSpeed();
//    Motor_BL.getSpeed();
//    Motor_FR.getSpeed();
//    Motor_FL.getSpeed();
}

bool cascade_complete(){
	return Motor_cas.goal_reached();
}

void cascade_monitor(float target_height){
	Motor_cas.setgoal(target_height);
}
