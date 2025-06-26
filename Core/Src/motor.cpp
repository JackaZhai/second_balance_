#include "global_variable.h"
#include "motor.h"
#include "jy901s.h"
#include "main.h"
#include "usart.h"
#include "gpio.h"

TB6612::TB6612(TIM_HandleTypeDef *htim_PWM,
               uint32_t CHANNEL1,
               uint32_t CHANNEL2,
               GPIO_TypeDef* AIN1_PORT, uint16_t AIN1_PIN,
               GPIO_TypeDef* AIN2_PORT, uint16_t AIN2_PIN,
               GPIO_TypeDef* BIN1_PORT, uint16_t BIN1_PIN,
               GPIO_TypeDef* BIN2_PORT, uint16_t BIN2_PIN,
               TIM_HandleTypeDef *htim_E1,
               TIM_HandleTypeDef *htim_E2)
{
    this->htim_PWM = htim_PWM;
    this->CHANNEL1 = CHANNEL1;
    this->CHANNEL2 = CHANNEL2;
    this->AIN1_PORT = AIN1_PORT;
    this->AIN1_PIN = AIN1_PIN;
    this->AIN2_PORT = AIN2_PORT;
    this->AIN2_PIN = AIN2_PIN;
    this->BIN1_PORT = BIN1_PORT;
    this->BIN1_PIN = BIN1_PIN;
    this->BIN2_PORT = BIN2_PORT;
    this->BIN2_PIN = BIN2_PIN;
    this->htim_E1 = htim_E1;
    this->htim_E2 = htim_E2;

}

void TB6612::set_duty1(int16_t duty)
{
    duty = (duty > this->duty_max) ? this->duty_max : (duty < -this->duty_max) ? -this->duty_max : duty;
    if (duty > 0)
    {
        HAL_GPIO_WritePin(this->AIN1_PORT, this->AIN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->AIN2_PORT, this->AIN2_PIN, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(this->htim_PWM, this->CHANNEL1, duty);
    }
    else
    {
        HAL_GPIO_WritePin(this->AIN1_PORT, this->AIN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(this->AIN2_PORT, this->AIN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(this->htim_PWM, this->CHANNEL1, -duty);
    }
}

void TB6612::set_duty2(int16_t duty)
{
    duty = (duty > this->duty_max) ? this->duty_max : (duty < -this->duty_max) ? -this->duty_max : duty;
    if (duty > 0)
    {
        HAL_GPIO_WritePin(this->BIN1_PORT, this->BIN1_PIN, GPIO_PIN_SET);
        HAL_GPIO_WritePin(this->BIN2_PORT, this->BIN2_PIN, GPIO_PIN_RESET);
        __HAL_TIM_SET_COMPARE(this->htim_PWM, this->CHANNEL2, duty);
    }
    else
    {
        HAL_GPIO_WritePin(this->BIN1_PORT, this->BIN1_PIN, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(this->BIN2_PORT, this->BIN2_PIN, GPIO_PIN_SET);
        __HAL_TIM_SET_COMPARE(this->htim_PWM, this->CHANNEL2, -duty);
    }
}

void TB6612::set_duty(int16_t duty1, int16_t duty2)
{
    this->set_duty1(duty1);
    this->set_duty2(duty2);
}

void TB6612::init(void)
{
    this->duty_max = this->htim_PWM->Init.Period + 1;
    HAL_TIM_PWM_Start(this->htim_PWM, this->CHANNEL1);
    HAL_TIM_PWM_Start(this->htim_PWM, this->CHANNEL2);
    HAL_TIM_Encoder_Start(this->htim_E1, TIM_CHANNEL_ALL);
    HAL_TIM_Encoder_Start(this->htim_E2, TIM_CHANNEL_ALL);
}

int16_t TB6612::get_duty_max(void)
{
    return this->duty_max;
}

