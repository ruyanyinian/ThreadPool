//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"

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
};


//// BUG1写法展示
//void createThreadPool(ThreadPool *threadPool, int maxThreads, int minThreads) {
//  threadPool->queueFront = 0;
//  threadPool->queueRear = 100; //TODO(qinyu)先随便赋值一个数
//  threadPool->taskQ = (Task *) malloc(sizeof(Task) * threadPool->queueSize); // 任务队列
//  threadPool->workingThreadIDs = (pthread_t *) malloc(sizeof(pthread_t) * maxThreads);
//
//  // 启动线程
//  for (int i = 0; i < maxThreads; ++i) {
//    // 目前这个threadPool->taskQ[i]里面没有任何初始化, 如果直接执行肯定报错
//    // 而且这样写的话是线程id 1~maxthreads必须和threadPool->taskQ[i]进行对应, 实际上他们是没有什么关系的.
//    pthread_create(&threadPool->workingThreadIDs[i], NULL, threadPool->taskQ[i].func, NULL);
//  }
//}

void *worker(void *arg) {
  ThreadPool *threadPool = (ThreadPool *)arg;


  threadPool->taskQ[0].func(arg); // 真正的函数执行在这里.

  return NULL;
}

void createThreadPool(ThreadPool *threadPool, int maxThreads, int minThreads) {
  threadPool->queueFront = 0;
  threadPool->queueCapacity = maxThreads;

  // 假设任务队列的和最大的线程数量是有关的, 也就是任务数量不可以超过最大的线程数量
  threadPool->taskQ = (Task *) malloc(sizeof(Task) * maxThreads);
  threadPool->workingThreadIDs = (pthread_t *) malloc(sizeof(pthread_t) * maxThreads);
  for (int i = 0; i < maxThreads; ++i) {
    /**
     * 一开始我在想为什么这里不是直接调用任务函数, 而是传递是以worker函数, 不仅仅自己的需求中分析的那样我们需要工作线程
     * 更是因为我们这里需要的是一个延迟的调用, 这里的worker更像是对真正线程函数的封装.
     * */
    pthread_create(&threadPool->workingThreadIDs[i], NULL, worker, threadPool);
  }

}

void destroyThreadPool(ThreadPool *threadPool) {

}

void threadPoolAdd(ThreadPool *threadPool, void *(*taskFunc)(void *arg), void *arg) {

}


