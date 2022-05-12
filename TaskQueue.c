//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"
#include "Queue.h"

// QUESTION: 我是不是应该把这个queue和task给拆开? 我们有两种写法:
//  1.就是定义一个结构体让然后里面的的func和args各定义一个queue.
//  2.就是定义一个task结构体, 然后声明func和arg两个变量. 然后task定义的变量在存放在queue中.
//  3.就是像作者一样把queue和task写在一起.

struct Task {
  ThreadFunc func;
  void *args;
};

void enTaskQueue(Queue *queue, Task *task) {
  enQueue(queue, task);
}

Task *deTaskQueue(Queue *queue) {
  Task *task = deQueue(queue);
  return task;
}

//Queue *createTaskQueue() {
//  TaskQueue *taskQueue = (TaskQueue*)malloc(sizeof(TaskQueue));
//  if (!taskQueue) {
//    printf("the storage is not enough!");
//    return NULL;
//  }
//  return taskQueue;
//}
//
//
////int getTaskQueueSize(TaskQueue *taskQueue) {
////  return getSize(taskQueue->funcQueue); // 只需要返回一个即可
////}
//
//void enTaskQueue(TaskQueue *taskQueue) {
////  enQueue(taskQueue->funcQueue, (void*)item);
////  enQueue(taskQueue->argQueue, args);
//
//}
//
////void *deTaskQueue(TaskQueue *taskQueue) {
////  return deQueue(taskQueue->funcQueue);
////}
//
////void *deArgsQueue(TaskQueue *taskQueue) {
////  return deQueue(taskQueue->argQueue);
////}


//void destroyTaskQueue(TaskQueue *taskQueue) {
//  destroyQueue(taskQueue->funcQueue);
//  destroyQueue(taskQueue->argQueue);
//}