//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"

typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型

struct TaskQueue {
  ThreadFunc *data;
  void *args;
  int size;
  int front;
  int rear; // rear怎么确定
  int capacity;
};

TaskQueue *createTaskQueue(int capacity) {
  TaskQueue *taskQueue = (TaskQueue*)malloc(sizeof(TaskQueue));
  if (!taskQueue) {
    printf("the storage is not enough!");
    return NULL;
  }
  taskQueue->data = (ThreadFunc*) malloc(capacity * sizeof(ThreadFunc));
  if (!taskQueue->data) {
    printf("the storage is not enough!");
    return NULL;
  }

//  taskQueue->args = malloc(sizeof(void *) * capacity);
//  if (!taskQueue->args) {
//    printf("cannot create array for args");
//    return NULL;
//  }

  taskQueue->capacity = capacity;
  taskQueue->front = 0;
  taskQueue->rear = -1;
  taskQueue->size = 0;
  return taskQueue;
}

int getSize(TaskQueue *taskQueue) {
  return taskQueue->size;
}
int isFull(TaskQueue *taskQueue) {
  return taskQueue->size == CAPACITY;
}

int isEmpty(TaskQueue *taskQueue) {
  return taskQueue->size == 0;
}

int enQueue(TaskQueue *taskQueue, ThreadFunc item) {
  if (isFull(taskQueue)) {
    printf("the queue is full, add failed!");
    return ERROR;
  }
  taskQueue->rear++;
  taskQueue->data[taskQueue->rear] = item;
  // 这里主要是如果rear和capacity取余数, 如果rear小于capcity就是正常的
  // 如果等于capacity的话, 那么rear=0, 然后就又回到原点了, 所以肯定还是不要超过capacity
  taskQueue->rear %= CAPACITY;
  taskQueue->size++;
  return CORRECT;
}

int deQueue(TaskQueue *taskQueue) {
  if (isEmpty(taskQueue)) {
    printf("the queue is empty, cannot dequeue");
    return ERROR;
  }
  taskQueue->front++;
  taskQueue->front %= CAPACITY;
  taskQueue->data[taskQueue->front] = 0;
  taskQueue->size--;
  return CORRECT;
}

ThreadFunc getFront(TaskQueue *taskQueue) {
  return taskQueue->data[taskQueue->front];
}

void destroyTaskQueue(TaskQueue *taskQueue) {
  if (taskQueue) {
    if (taskQueue->data) {
      for (int i = 0; i < taskQueue->size; ++i) {
        taskQueue->data[i] = 0;
      }
      free(taskQueue->data);
      taskQueue->data = NULL;
    }
    free(taskQueue);
    taskQueue = NULL;
  }
}

void setArgs(TaskQueue *taskQueue, void *args) {
  taskQueue->args = args;
}

void *getArgs(TaskQueue *taskQueue) {
  return taskQueue->args;
}




