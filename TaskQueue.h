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

int enQueue(TaskQueue *taskQueue, ThreadFunc item); // 入队, 入队成功返回0, 入队失败返回的是不为0的错误码
ThreadFunc deQueue(TaskQueue *taskQueue); // 出队, 出队成功返回0, 入队失败返回的是不为0的错误码
int getSize(TaskQueue *taskQueue);
int getCapacity(TaskQueue *taskQueue);
//ThreadFunc getFront(TaskQueue *taskQueue);

void setArgs(TaskQueue *taskQueue, void *arg);
void *getArgs(TaskQueue *taskQueue);

void destroyTaskQueue(TaskQueue *taskQueue);
#endif //THREADPOOL_TASKQUEUE_H
