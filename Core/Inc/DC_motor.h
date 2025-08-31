/*
 * DC_motor.h
 *
 *  Created on: Jul 8, 2025
 *      Author: USER
 */

#ifndef INC_DC_MOTOR_H_
#define INC_DC_MOTOR_H_

#include "stm32f4xx_hal.h"

extern float total_turns;
extern float cm_per_turn;
extern float total_high;
extern float turn;
extern float height;
extern float target_turns;

class DC_motor{
public:
	void setup();
	void PI_run();
	void update_speed(int sign);
	float get_speed() const { return speed; }
	void setspeed(float target_speed);
	void stepTo(int32_t steps);
	void heightTo(float high);
	void set_motor_parameter(float reduction_ratio,int resolution) ;
	void set_PID_parameter(float _kp,float _ki);

	DC_motor(TIM_HandleTypeDef *_enc_htim, GPIO_TypeDef *_dirPort, uint16_t _dirPin, TIM_HandleTypeDef *_PWM_htim,
			uint32_t _PWM_TIM_CHANNEL,bool _dirpin,float _kp,float _ki) {
		enc_htim = _enc_htim;
		dirPort = _dirPort;
		dirPin = _dirPin;
		PWM_htim = _PWM_htim;
		PWM_TIM_CHANNEL = _PWM_TIM_CHANNEL;
		dir_pin = _dirpin;
		kp = _kp;
	    ki = _ki;
	};
private:
	//PID parameter
	float kp = 0.f ,ki = 0.f,kd = 0.f;
	//error
	float error = 0.f,pre_error = 0.f,integral = 0.f,differential = 0.f;
	//sp of velocity
	float speed = 0.f;
	float sp = 0.f;
	//float turn = 0.f;
	//motor and encoder information
	float span = 0.001;
	int resolution = 100;
	float reduction_ratio = 64.f;
	int dir = 0;
	int arr = 999;
	bool dir_pin = 0;
	int pulse = 0;
	
	float u = 0.f;
	TIM_HandleTypeDef *enc_htim;
	//motor driver
	GPIO_TypeDef *dirPort;
	uint16_t dirPin;
	TIM_HandleTypeDef *PWM_htim;
	uint32_t PWM_TIM_CHANNEL;

};


#endif /* INC_DC_MOTOR_H_ */
