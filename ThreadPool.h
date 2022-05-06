//
// Created by qinyu on 2022/5/5.
//

#ifndef THREADPOOL_THREADPOOL_H
#define THREADPOOL_THREADPOOL_H

#include <stdio.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>
typedef struct Task {
  void *(*func)(void*);
  void *arg;
}Task;

struct ThreadPool {
  // threadPool维护一个任务队列
  Task *taskQ; // 任务队列
  int queueFront; // 队首
  int queueRear; // 队尾
  int queueSize;
  int queueCapacity;

  // threadPool相关的线程数量
  int maxThreads;
  int minThreads;
  // 线程相关
  pthread_t *workingThreadIDs, managerThreadID;

  // 互斥锁
  pthread_mutex_t threadPoolMutex;
  pthread_cond_t  workingCond;
};


typedef struct ThreadPool ThreadPool;

void createThreadPool(ThreadPool *threadPool, int maxThreads, int minThreads); // threadPool的初始化
void destroyThreadPool(ThreadPool *threadPool);
void threadPoolAdd(ThreadPool *threadPool, void *(*taskFunc)(void *), void *arg);

#endif //THREADPOOL_THREADPOOL_H
