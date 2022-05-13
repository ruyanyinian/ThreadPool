//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"
// QUESTION: 我是不是应该把这个queue和task给拆开? 我们有两种写法:
//  1.就是定义一个结构体让然后里面的的func和args各定义一个queue.
//  2.就是定义一个task结构体, 然后声明func和arg两个变量. 然后task定义的变量在存放在queue中.
//  3.就是像作者一样把queue和task写在一起. 下面就是第三种写法

typedef void *(*ThreadFunc)(void *); // 这里定义一个函数指针类型

struct TaskQueue {
//  ThreadFunc *data;
//  void **args;
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
//  taskQueue->data = (ThreadFunc*) malloc(capacity * sizeof(ThreadFunc));
//  taskQueue->args = (void**) malloc(capacity * sizeof(void*));
//  taskQueue->returnTask = (Task*)malloc(sizeof(Task));
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
//  Task *task; // QUESTION: 怎么同时返回两个值? 可能只能用struct结构体返回.
//  task->data = (ThreadFunc*)taskQueue->data[taskQueue->front];
//  task->args = taskQueue->args[taskQueue->front];
//  Task *task = taskQueue->returnTask;
//  task->data = (ThreadFunc)taskQueue->data[taskQueue->front];
//  task->args = taskQueue->args[taskQueue->front];
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
