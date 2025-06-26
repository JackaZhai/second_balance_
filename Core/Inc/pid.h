#ifndef PID_H
#define PID_H


typedef enum
{
    positional,
    velocity
} pid_mode;

class PID_Controller
{
    private:
        float error;
        float last_error;
        float last_last_error;
        float error_sum;
        float output;
        pid_mode mode;
    public:
        float Kp;
        float Ki;
        float Kd;
        float *actual;
        float *target;
        PID_Controller(float Kp, float Ki, float Kd, pid_mode mode,float* actual,float* target);
        float pid_figure(float special);
        float *get_output(void);
};



#endif

