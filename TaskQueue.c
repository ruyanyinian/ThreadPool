//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"

typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型

struct TaskQueue {
  Task *task;
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
  taskQueue->task = (Task*) malloc(sizeof(Task) * capacity);
  if (!taskQueue->task) {
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

void enQueue(TaskQueue *taskQueue, Task item) {
  if (isFull(taskQueue)) {
    printf("the queue is full, add failed!");
    return;
  }
  taskQueue->rear++;
  taskQueue->task[taskQueue->rear] = item;
  taskQueue->rear %= taskQueue->capacity;
  taskQueue->size++;
}

Task deQueue(TaskQueue *taskQueue) {
  if (isEmpty(taskQueue)) {
    printf("the queue is empty, cannot dequeue");
  }
  taskQueue->front++;
  taskQueue->front %= taskQueue->capacity;
  taskQueue->size--;

  return taskQueue->task[taskQueue->front];
}


void destroyTaskQueue(TaskQueue *taskQueue) {
  if (taskQueue) {
    //QUESTION: 析构task, 我们的task应该是一个数组, 而且接受的是外部开辟的空间, 为什么不释放外部开辟的空间?
    if (taskQueue->task) {
      free(taskQueue->task);
      taskQueue->task = NULL;
    }
    free(taskQueue);
    taskQueue = NULL;
  }
}


int getCapacity(TaskQueue *taskQueue) {
  return taskQueue->capacity;
}
