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
#include "global_variable.h"

vofa::vofa(UART_HandleTypeDef *huart)
{
    this->huart = huart;
}
void vofa::init(void)
{
    HAL_UARTEx_ReceiveToIdle_IT(this->huart, this->data, 30);
}
float vofa::analysis_data(void)
{
	uint8_t i=0;
    uint8_t data_Start_Num = 0; //记录数据位开始的地方
    uint8_t data_End_Num = 0; //记录数据位结束的地方
    uint8_t data_Num = 0; //记录数据位数
    uint8_t minus_Flag = 0; //判断是否为负数
    float data_return = 0; // 解析得到的数据
    for(i=0;i<200;i++) // 查找等于号和感叹号的位置
    {
        if(this->data[i] == '=') data_Start_Num = i + 1; // +1是直接定位到数据开始的地方
        if(this->data[i] == '!')
        {
            data_End_Num = i - 1;
            break;
        }
    }
    if(this->data[data_Start_Num] == '-') // 如果是负数
    {
        data_Start_Num += 1; // 后移一位到数据位
        minus_Flag = 1; // 负数flag
    }
    data_Num = data_End_Num - data_Start_Num + 1;
    if(data_Num == 4) //数据共3位
		{
        data_return = (this->data[data_Start_Num]-48)  + (this->data[data_Start_Num+2]-48)*0.1f +(this->data[data_Start_Num+3]-48)*0.01f;
    }
    else if(data_Num == 5) //数据共4位
    {
        data_return = (this->data[data_Start_Num]-48)*10 + (this->data[data_Start_Num+1]-48) + (this->data[data_Start_Num+3]-48)*0.1f +(this->data[data_Start_Num+4]-48)*0.01f;
    }
    else if(data_Num == 6) //数据共5位
    {
        data_return = (this->data[data_Start_Num]-48)*100 + (this->data[data_Start_Num+1]-48)*10 + (this->data[data_Start_Num+2]-48) +(this->data[data_Start_Num+4]-48)*0.1f + (this->data[data_Start_Num+5]-48)*0.01f;
    }
    if(minus_Flag == 1)  data_return = -data_return;
    return data_return;
}

void vofa::read_data(void)
{
	if(this->data[0] == 'u')
    {
        if(this->data[1] == 'P')
        {
            up.Kp = this->analysis_data();
        }
        else if(this->data[1] == 'D')
        {
            up.Kd = this->analysis_data();
        }
    }
    else if(this->data[0] == 's')
    {
        if(this->data[1] == 'P')
        {
            rate.Kp = this->analysis_data();
        }
        else if(this->data[1] == 'I')
        {
            rate.Ki = this->analysis_data();
        }
    }
}


