#include "jy901s.h"
#include "main.h"
#include "usart.h"
#include "string.h"
#include "tim.h"
#include "gpio.h"
#include "callback.h"
#include "global_variable.h"
#include <stdio.h>
#include "vofa.h"

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if (huart == imu.huart)
    {
        imu.update();
        up.pid_figure(med_angle);
        motor.set_duty((int16_t)*up.get_output(), (int16_t)*up.get_output());
        HAL_UARTEx_ReceiveToIdle_IT(imu.huart, imu.data, 11);
    }
    else if(huart == debug.huart)
    {
        debug.read_data();

        HAL_UARTEx_ReceiveToIdle_IT(debug.huart, debug.data,30);
    }
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if (htim == &htim6)
    {
        tick_ms++;
    }
}
