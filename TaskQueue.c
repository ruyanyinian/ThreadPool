//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"

typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型

struct Task {
  ThreadFunc data;
  void *args;
};

struct TaskQueue {
  ThreadFunc *data;
  void **args;
  Task *returnTask;
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
  taskQueue->args = (void**) malloc(capacity * sizeof(void*));
  taskQueue->returnTask = (Task*)malloc(sizeof(Task));
  if (!taskQueue->data) {
    printf("the storage is not enough!");
    return NULL;
  }

  taskQueue->capacity = capacity;

//  taskQueue->args = malloc(sizeof(void *) * capacity);
//  if (!taskQueue->args) {
//    printf("cannot create array for args");
//    return NULL;
//  }

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

void enQueue(TaskQueue *taskQueue, ThreadFunc item, void *arg) {
  if (isFull(taskQueue)) {
    printf("the queue is full, add failed!");
    return;
  }
  taskQueue->rear++;
  taskQueue->data[taskQueue->rear] = item;
  taskQueue->args[taskQueue->rear] = arg;
  // 这里主要是如果rear和capacity取余数, 如果rear小于capcity就是正常的
  // 如果等于capacity的话, 那么rear=0, 然后就又回到原点了, 所以肯定还是不要超过capacity

  taskQueue->rear %= taskQueue->capacity;
  taskQueue->size++;
}

Task *deQueue(TaskQueue *taskQueue) {
  if (isEmpty(taskQueue)) {
    printf("the queue is empty, cannot dequeue");
//    return ERROR;
  }
  taskQueue->front++;
  taskQueue->front %= taskQueue->capacity;
  taskQueue->size--;
//  Task *task; // QUESTION: 怎么同时返回两个值? 可能只能用struct结构体返回.
//  task->data = (ThreadFunc*)taskQueue->data[taskQueue->front];
//  task->args = taskQueue->args[taskQueue->front];
  Task *task = taskQueue->returnTask;
  task->data = (ThreadFunc)taskQueue->data[taskQueue->front];
  task->args = taskQueue->args[taskQueue->front];
  return task;
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
//
//void *getArgs(TaskQueue *taskQueue) {
//  return taskQueue->args;
//}

int getCapacity(TaskQueue *taskQueue) {
  return taskQueue->capacity;
}

ThreadFunc getFunc(Task *task) {
  return task->data;
}

void *getArgs(Task *task) {
  return task->args;
}
