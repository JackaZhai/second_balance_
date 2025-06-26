#ifndef __GLOBAL_VARIABLE_H
#define __GLOBAL_VARIABLE_H

#include "jy901s.h"
#include "motor.h"
#include "tim.h"
#include "gpio.h"
#include "callback.h"
#include "main.h"
#include "string.h"
#include "usart.h"
#include "task.h"
#include "pid.h"
#include "vofa.h"

extern jy901s imu;
extern TB6612 motor;
extern task_TCB task_fifo[task_num];
extern uint32_t tick_ms;
extern float const_zero;
extern PID_Controller rate;
extern PID_Controller up;
extern float med_angle;
extern vofa debug;
extern float encoder_sum;

#endif
