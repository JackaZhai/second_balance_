#include "main.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "jy901s.h"

jy901s::jy901s(UART_HandleTypeDef *huart)
{
    this->huart = huart;
}

void jy901s::update(void)
{
    if(this->data[1] == 0x53)
    {
        this->Roll = (float)((int16_t)((this->data[3] << 8) | this->data[2])) / 32768.0f * 180.0f;
        this->Pitch = (float)((int16_t)((this->data[5] << 8) | this->data[4])) / 32768.0f * 180.0f;
        this->Yaw = (float)((int16_t)((this->data[7] << 8) | this->data[6])) / 32768.0f * 180.0f;
    }
}
float* jy901s::getYaw(void)
{
    return &this->Yaw;
}
float* jy901s::getPitch(void)
{
    return &this->Pitch;
}
float* jy901s::getRoll(void)
{
    return &this->Roll;
}

void jy901s::init(void)
{
    this->unlock[0]=0xFF;
    this->unlock[1]=0xAA;
    this->unlock[2]=0x69;
    this->unlock[3]=0x88;
    this->unlock[4]=0xB5;

    this->save[0]=0xFF;
    this->save[1]=0xAA;
    this->save[2]=0x00;
    this->save[3]=0x00;
    this->save[4]=0x00;

    this->adjust_z[0]=0xFF;
    this->adjust_z[1]=0xAA;
    this->adjust_z[2]=0x01;
    this->adjust_z[3]=0x04;
    this->adjust_z[4]=0x00;

    //this->zero();
    HAL_UARTEx_ReceiveToIdle_IT(this->huart, this->data, 11);
}

void jy901s::zero(void)
{
    HAL_UART_Transmit(this->huart, this->unlock, sizeof(this->unlock), HAL_MAX_DELAY);
    HAL_Delay(200);
	HAL_UART_Transmit(this->huart, this->adjust_z, sizeof(this->adjust_z), HAL_MAX_DELAY);
    HAL_Delay(3000);
    HAL_UART_Transmit(this->huart, this->save, sizeof(this->save), HAL_MAX_DELAY);
}

