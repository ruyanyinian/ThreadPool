//
// Created by qinyu on 2022/5/7.
//

#ifndef THREADPOOL_TASKQUEUE_H
#define THREADPOOL_TASKQUEUE_H

#include <stdio.h>
#include <stdlib.h>

#define CAPACITY 100
#define ERROR -99 // 一般来说我们定义一个
#define CORRECT 0
// 错误标志
typedef struct TaskQueue TaskQueue;
typedef void *(*ThreadFunc)(void *); // 在队列中存放的函数指针


TaskQueue *createTaskQueue(int capacity);
int getTaskQueueSize(TaskQueue *taskQueue);
void enTaskQueue(TaskQueue *taskQueue, ThreadFunc item, void *args);
void *deTaskFuncQueue(TaskQueue *taskQueue);
void *deArgsQueue(TaskQueue *taskQueue);
void destroyTaskQueue(TaskQueue *taskQueue);

#endif //THREADPOOL_TASKQUEUE_H
