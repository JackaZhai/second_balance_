#ifndef TASK_H
#define TASK_H

#include <stdint.h>

#define task_num 5
#define __IS_TCB_INITED(TCB) ((TCB.Task==NULL)?0:1)
#define __IS_TCB_UNINITED(TCB) ((TCB.Task==NULL)?1:0)
#define __GET_NOW_TICK() (tick_ms)

typedef int(slice_task)(void* arg);

struct task_TCB
{
    slice_task* Task;          // 任务函数的函数指针
    void* arg;                 // 传给任务函数的数据指针
    uint32_t period;           // 任务周期
    uint32_t moment;           // 任务下次执行的时间点
};

void task_init(task_TCB *task);
task_TCB *task_register(slice_task* task_func, void *arg, uint32_t period);
void task_scheduler(void);
int LED_task(void* arg);
void TCB_init(void);
int vofa_task(void* arg);


#endif 



