#include "jy901s.h"
#include "motor.h"
#include "tim.h"
#include "gpio.h"
#include "callback.h"
#include "global_variable.h"
#include "main.h"
#include "string.h"
#include "usart.h"
#include "task.h"
#include "pid.h"

float encoder_sum;
float const_zero = 0;
float med_angle = -2;
jy901s imu(&huart2);
TB6612 motor(&htim2, TIM_CHANNEL_1, TIM_CHANNEL_2,
                AIN1_GPIO_Port, AIN1_Pin,
                AIN2_GPIO_Port, AIN2_Pin,
                BIN1_GPIO_Port, BIN1_Pin,
                BIN2_GPIO_Port, BIN2_Pin,
                &htim3, &htim4);
task_TCB task_fifo[task_num];
uint32_t tick_ms;
PID_Controller rate(0,0,0, positional, &encoder_sum, &const_zero);
PID_Controller up(-117,0,-5.44,positional,imu.getRoll(),rate.get_output());
vofa debug(&huart1);

