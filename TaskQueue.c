//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"

typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型
// QUESTION: 我是不是应该把这个queue和task给拆开?
struct TaskQueue {
  ThreadFunc *data;
  void **args;
  int size;
  int front;
  int rear;
  int capacity;
};

TaskQueue *createTaskQueue(int capacity) {
  TaskQueue *taskQueue = (TaskQueue*)malloc(sizeof(TaskQueue));

  if (!taskQueue) {
    printf("the storage is not enough!");
    return NULL;
  }
  taskQueue->data = (ThreadFunc*) malloc(capacity * sizeof(ThreadFunc));
  taskQueue->args = malloc(capacity* sizeof(void*));
  if (!taskQueue->data || taskQueue->args) {
    printf("the storage is not enough!");
    return NULL;
  }

  taskQueue->capacity = capacity;

  taskQueue->front = -1;
  taskQueue->rear = -1;
  taskQueue->size = 0;
  return taskQueue;
}

int getSize(TaskQueue *taskQueue) {
  return taskQueue->size;
}
int isFull(TaskQueue *taskQueue) {
  return taskQueue->size == taskQueue->capacity;
}

int isEmpty(TaskQueue *taskQueue) {
  return taskQueue->size == 0;
}

int enQueue(TaskQueue *taskQueue, ThreadFunc item, void *args) {
  if (isFull(taskQueue)) {
    printf("the queue is full, add failed!");
    return ERROR;
  }
  taskQueue->rear++;
  taskQueue->data[taskQueue->rear] = item;
  taskQueue->args[taskQueue->rear] = args;
  // 这里主要是如果rear和capacity取余数, 如果rear小于capcity就是正常的
  // 如果等于capacity的话, 那么rear=0, 然后就又回到原点了, 所以肯定还是不要超过capacity
  taskQueue->rear %= taskQueue->capacity;
  taskQueue->size++;
  return CORRECT;
}

ThreadFunc deQueue(TaskQueue *taskQueue) {
  if (isEmpty(taskQueue)) {
    printf("the queue is empty, cannot dequeue");
    return ERROR;
  }
  taskQueue->front++;
  taskQueue->front %= taskQueue->capacity;
  taskQueue->size--;
  return taskQueue->data[taskQueue->front];
}

void destroyTaskQueue(TaskQueue *taskQueue) {
  if (taskQueue) {
    if (taskQueue->data) {
      for (int i = 0; i < taskQueue->capacity; ++i) {
        taskQueue->data[i] = 0;
      }
      free(taskQueue->data);
      taskQueue->data = NULL;
    }

    if (taskQueue->args) {
      free(taskQueue->args);
      taskQueue->args = NULL;
    }
    free(taskQueue);
    taskQueue = NULL;
  }
}

//void setArgs(TaskQueue *taskQueue, void *args) {
//  taskQueue->args = args;
//}

void *getArgs(TaskQueue *taskQueue) {
  return taskQueue->args;
}

int getCapacity(TaskQueue *taskQueue) {
  return taskQueue->capacity;
}
