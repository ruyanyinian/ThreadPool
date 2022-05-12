//
// Created by qinyu on 2022/5/12.
//

#include "Queue.h"
// QUESTION: C语言怎么定义一个可以存放多种变量的容器? 因为毕竟函数指针和它的参数的数据类型是不同的.
//  我想到一个方案是定义一个结构体, 然后这个结构体当作一个数据类型, 然后这个结构体封装了两种数据类型, 比如一个函数指针, 一个参数类型的.
typedef struct Queue {
  void **data; // 存放的是一个指针变量. 但是它
  int size;
  int front;
  int rear;
  int capacity;
} Queue;

