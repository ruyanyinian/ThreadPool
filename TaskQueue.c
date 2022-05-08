//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"

typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型

// QUESTION: 我们想把结构体的部分信息暴漏出去, 比如这里的data, 因为我们想在外部进行访问,怎么办?
// 方法: 我们可以写一个函数, 然后返回这个成员变量就可以了.
struct TaskQueue {
  ThreadFunc *data; // NOTE: 注意这里应该加上*
  int size;
  int front;
  int rear; // rear怎么确定
};

TaskQueue *createTaskQueue() {
  TaskQueue *taskQueue = (TaskQueue*)malloc(sizeof(TaskQueue));
  if (!taskQueue) {
    printf("the storage is not enough!");
    return NULL;
  }
  taskQueue->data = (ThreadFunc*) malloc(CAPACITY * sizeof(ThreadFunc));
  if (!taskQueue->data) {
    printf("the storage is not enough!");
    return NULL;
  }

  taskQueue->front = -1;
  taskQueue->rear = -1;
  taskQueue->size = 0;
  return taskQueue;
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

ThreadFunc getFront(TaskQueue *taskQueue, int index) {

  return taskQueue->data[index];
}

void queueDestroy(TaskQueue *taskQueue) {
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