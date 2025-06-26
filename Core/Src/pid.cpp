#include <stdio.h>
#include "jy901s.h"
#include "main.h"
#include "usart.h"
#include "string.h"
#include "tim.h"
#include "gpio.h"
#include "callback.h"
#include "global_variable.h"
#include "pid.h"

float PID_Controller::pid_figure(float special)
{
    this->error = (*this->target + special) - *this->actual;
    if(this->mode == positional)
    {
        this->error_sum += this->error;
        this->output = this->Kp * this->error 
                    + this->Ki * this->error_sum 
                    + this->Kd * (this->error - this->last_error);
        this->last_error = this->error;   
    }
    else if(this->mode == velocity)
    {
        this->output = this->Kp * (this->error - this->last_error) 
                    + this->Ki * this->error 
                    + this->Kd * (this->error - 2 * this->last_error + this->last_last_error);
        this->last_last_error = this->last_error;
        this->last_error = this->error;
    }
    return this->output;
}

PID_Controller::PID_Controller(float Kp, float Ki, float Kd, pid_mode mode,float* actual,float* target)
{
    this->Kp = Kp;
    this->Ki = Ki;
    this->Kd = Kd;
    this->error = 0;
    this->last_error = 0;
    this->last_last_error = 0;
    this->error_sum = 0;
    this->actual = actual;
    this->target = target;
    this->output = 0;
    this->mode = mode;
}

float* PID_Controller::get_output(void)
{
    return &this->output;
}