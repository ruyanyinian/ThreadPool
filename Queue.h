//
// Created by qinyu on 2022/5/12.
//

#ifndef THREADPOOL_QUEUE_H
#define THREADPOOL_QUEUE_H
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 100
#define ERROR -99 // 一般来说我们定义一个
#define CORRECT 0
// 错误标志
typedef struct Queue Queue;
//typedef void *(*ThreadFunc)(void *); // 在队列中存放的函数指针

Queue *createQueue(int capacity);

int enQueue(Queue *queue, void *item); // 入队, 入队成功返回0, 入队失败返回的是不为0的错误码
void *deQueue(Queue *queue); // 出队, 出队成功返回0, 入队失败返回的是不为0的错误码
int getSize(Queue *queue);
int getCapacity(Queue *queue);
//ThreadFunc getFront(TaskQueue *taskQueue);

//void setArgs(Queue *Queue, void *arg);
//void *getArgs(Queue *queue);
void destroyQueue(Queue *queue);

#endif //THREADPOOL_QUEUE_H
