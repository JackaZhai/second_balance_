#include "task.h"
#include "usart.h"
#include "string.h"
#include "tim.h"
#include "gpio.h"
#include "callback.h"
#include "global_variable.h"
#include <stdio.h>


void task_init(task_TCB *task)
{
    memset(task, 0, sizeof(task_TCB));
}

task_TCB *task_register(slice_task* task_func, void *arg, uint32_t period)
{
    for (int i = 0; i < task_num; i++)
    {
        if (__IS_TCB_UNINITED(task_fifo[i]))
        {
            task_fifo[i].Task = task_func;
            task_fifo[i].arg = arg;
            task_fifo[i].period = period;
            task_fifo[i].moment = __GET_NOW_TICK() + period;
            return &task_fifo[i];
        }
    }
    return NULL; 
}

void task_scheduler(void)
{
    for (int i = 0; i < task_num; i++)
    {
        if (__IS_TCB_INITED(task_fifo[i]))
        {
            
            if(task_fifo[i].moment <= __GET_NOW_TICK())
            {
                task_fifo[i].moment = __GET_NOW_TICK() + task_fifo[i].period;
                task_fifo[i].Task(task_fifo[i].arg);
            }
        }
    }
}

int LED_task(void* arg)
{
    LED_TURN;
    return 1;
}
int vofa_task(void* arg)
{
    char data_string[30];
    //sprintf(data_string, "%.2f,%.2f,%.2f,%.2f,%.2f\r\n", *up.actual,*up.target,*up.get_output(),rate.Kp,rate.Kd);
    sprintf(data_string, "%.2f,%.2f,%.2f,%.2f,%.2f\r\n", *rate.actual,*rate.target,*up.get_output(),rate.Kp,rate.Ki);
    HAL_UART_Transmit(&huart1, (uint8_t*)data_string, strlen(data_string), HAL_MAX_DELAY);
    return 1;
}
int encoder_task(void* arg)
{
    TB6612 *motor_t = (TB6612*)arg;
    motor_t->encoder_L = (short)__HAL_TIM_GET_COUNTER(motor_t->htim_E1);
    motor_t->encoder_R = -(short)__HAL_TIM_GET_COUNTER(motor_t->htim_E2);
    __HAL_TIM_SET_COUNTER(motor_t->htim_E1, 0);
    __HAL_TIM_SET_COUNTER(motor_t->htim_E2, 0);
    encoder_sum =  (float)(motor_t->encoder_L + motor_t->encoder_R);
    
    rate.Ki = 1.0f * rate.Kp / 200.0f;
    rate.pid_figure(0);

    return 1;
}
void TCB_init(void)
{
    task_register(&LED_task, NULL, 500);
    task_register(&vofa_task, NULL, 1);
    task_register(&encoder_task, &motor, 20);
    HAL_TIM_Base_Start_IT(&htim6);
}




