#ifndef MOTOR_MONITOR_H
#define MOTOR_MONITOR_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes */
void motor_monitor(void);
void cascade_monitor(float target_height);
bool cascade_complete();

#ifdef __cplusplus
void motor_init();

}
#endif

#endif /* MOTOR_MONITOR_H */
