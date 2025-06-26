#ifndef __VOFA_H
#define __VOFA_H


class vofa
{
    public:
        UART_HandleTypeDef *huart;
        vofa(UART_HandleTypeDef *huart);
        uint8_t data[30];
        float analysis_data(void);
        void read_data(void);
        void init(void);
};



#endif
