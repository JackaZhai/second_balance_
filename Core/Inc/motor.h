#ifndef __MOTOR_H
#define __MOTOR_H

#include "main.h"
#include "usart.h"
#include "jy901s.h"

class TB6612
{
private:
    int16_t duty_max;
    uint32_t CHANNEL1;
    uint32_t CHANNEL2;
    GPIO_TypeDef* AIN1_PORT;
    uint16_t AIN1_PIN;
    GPIO_TypeDef* AIN2_PORT;
    uint16_t AIN2_PIN;
    GPIO_TypeDef* BIN1_PORT;
    uint16_t BIN1_PIN;
    GPIO_TypeDef* BIN2_PORT;
    uint16_t BIN2_PIN;
    TIM_HandleTypeDef *htim_PWM;

public:
    TB6612(TIM_HandleTypeDef *htim_PWM,
           uint32_t CHANNEL1,
           uint32_t CHANNEL2,
           GPIO_TypeDef* AIN1_PORT, uint16_t AIN1_PIN,
           GPIO_TypeDef* AIN2_PORT, uint16_t AIN2_PIN,
           GPIO_TypeDef* BIN1_PORT, uint16_t BIN1_PIN,
           GPIO_TypeDef* BIN2_PORT, uint16_t BIN2_PIN,
           TIM_HandleTypeDef *htim_E1,
           TIM_HandleTypeDef *htim_E2);
    void set_duty1(int16_t duty);
    void set_duty2(int16_t duty);
    void set_duty(int16_t duty1, int16_t duty2);
    void init(void);
    int16_t get_duty_max(void);
    int16_t encoder_L;
    int16_t encoder_R;
    TIM_HandleTypeDef *htim_E1;
    TIM_HandleTypeDef *htim_E2;
};
#endif


