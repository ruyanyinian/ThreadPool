//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"

typedef struct Task {
  void* (*func)(void*);
  void* arg;
}Task;

typedef struct ThreadPool {
  Task* taskQ; // 任务队列

  int queueCapacity;
  int queueMax;
  int queueMin;
  int queueFront; // 队首
  int queueRear; // 队尾

  // 互斥锁

}ThreadPool;

