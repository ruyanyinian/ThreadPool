//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"
#include "Queue.h"
typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型
// QUESTION: 我是不是应该把这个queue和task给拆开?
struct TaskQueue {
  Queue *funcQueue;
  Queue *argQueue;
};

TaskQueue *createTaskQueue(int capacity) {
  TaskQueue *taskQueue = (TaskQueue*)malloc(sizeof(TaskQueue));

  if (!taskQueue) {
    printf("the storage is not enough!");
    return NULL;
  }
  taskQueue->funcQueue = createQueue(capacity);
  taskQueue->argQueue = createQueue(capacity);
  if (!taskQueue->funcQueue || !taskQueue->argQueue) {
    printf("the storage is not enough!");
    return NULL;
  }
  return taskQueue;
}


int getTaskQueueSize(TaskQueue *taskQueue) {
  return getSize(taskQueue->funcQueue); // 只需要返回一个即可
}

void enTaskQueue(TaskQueue *taskQueue, ThreadFunc item, void *args) {
  enQueue(taskQueue->funcQueue, (void*)item);
  enQueue(taskQueue->argQueue, args);
}

void *deTaskFuncQueue(TaskQueue *taskQueue) {
  return deQueue(taskQueue->funcQueue);
}

void *deArgsQueue(TaskQueue *taskQueue) {
  return deQueue(taskQueue->argQueue);
}


void destroyTaskQueue(TaskQueue *taskQueue) {
  destroyQueue(taskQueue->funcQueue);
  destroyQueue(taskQueue->argQueue);
}