#ifndef __JY901S_H
#define __JY901S_H

#ifdef __cplusplus
#include <stdint.h>
#include "usart.h"

class jy901s
{
private:
    float Yaw;
    float Pitch;   
    float Roll;
    uint8_t unlock[5];
    uint8_t save[5];
    uint8_t adjust_z[5];
public:
    jy901s(UART_HandleTypeDef *huart);
    UART_HandleTypeDef *huart;
    uint8_t data[11];
    void update(void);
    float* getYaw(void);
    float* getPitch(void);
    float* getRoll(void);
    void init(void);
    void zero(void);
};

#endif
#endif
