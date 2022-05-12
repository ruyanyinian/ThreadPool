//
// Created by qinyu on 2022/5/12.
//

#include "Queue.h"
// QUESTION: C语言怎么定义一个可以存放多种变量的容器? 因为毕竟函数指针和它的参数的数据类型是不同的.
//  我想到一个方案是定义一个结构体, 然后这个结构体当作一个数据类型, 然后这个结构体封装了两种数据类型, 比如一个函数指针, 一个参数类型的.


struct Queue {
  void **data; // 存放的是一个指针变量. 但是它
  int size;
  int front;
  int rear;
  int capacity;
};

Queue *createQueue(int capacity) {
  Queue *queue = (Queue*)malloc(sizeof(Queue));

  if (!queue) {
    printf("the storage is not enough!");
    return NULL;
  }
  queue->data = (void**) malloc(capacity * sizeof(void*));
//  queue->args = malloc(capacity* sizeof(void*));
//  if (!queue->data || queue->args) {
//    printf("the storage is not enough!");
//    return NULL;
//  }
  if (!queue->data) {
    printf("the storage is not enough!");
    return NULL;
  }

  queue->capacity = capacity;
  queue->front = -1;
  queue->rear = -1;
  queue->size = 0;
  return queue;
}

int getSize(Queue *queue) {
  return queue->size;
}
int isFull(Queue *queue) {
  return queue->size == queue->capacity;
}

int isEmpty(Queue *queue) {
  return queue->size == 0;
}

int enQueue(Queue *queue, void *item) {
  if (isFull(queue)) {
    printf("the queue is full, add failed!");
    return ERROR;
  }
  queue->rear++;
  queue->data[queue->rear] = item;
//  queue->args[queue->rear] = args;
  // 这里主要是如果rear和capacity取余数, 如果rear小于capcity就是正常的
  // 如果等于capacity的话, 那么rear=0, 然后就又回到原点了, 所以肯定还是不要超过capacity
  queue->rear %= queue->capacity;
  queue->size++;
  return CORRECT;
}

void *deQueue(Queue *queue) {
  if (isEmpty(queue)) {
    printf("the queue is empty, cannot dequeue");
    return ERROR;
  }
  queue->front++;
  queue->front %= queue->capacity;
  queue->size--;
  return queue->data[queue->front];
}

void destroyQueue(Queue *queue) {
  if (queue) {
    if (queue->data) {
      for (int i = 0; i < queue->capacity; ++i) {
        queue->data[i] = 0;
      }
      free(queue->data);
      queue->data = NULL;
    }

//    if (queue->args) {
//      free(queue->args);
//      queue->args = NULL;
//    }
    free(queue);
    queue = NULL;
  }
}

//void setArgs(Queue *queue, void *args) {
//  queue->args = args;
//}

//void *getArgs(Queue *queue) {
//  return queue->args;
//}

int getCapacity(Queue *queue) {
  return queue->capacity;
}
