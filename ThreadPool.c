//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"
#include "TaskQueue.h"

struct ThreadPool {
  // threadPool维护一个任务队列
  TaskQueue *taskQueue;

  // threadPool相关的线程数量
  int maxThreads;
  int minThreads;
  int busyNum;
  // 线程相关
  pthread_t *workingThreadIDs, managerThreadID;

  // 互斥锁
  pthread_mutex_t threadPoolMutex;
  pthread_cond_t  workingCond;
};


void *worker(void *arg) {
  // 这里是不是得加上一个条件变量?
  ThreadPool *threadPool = (ThreadPool*)arg;
  TaskQueue *taskQueue = threadPool->taskQueue;

  pthread_mutex_lock(&threadPool->threadPoolMutex); // 只有一个线程通过, 并且取值
  if (getSize(taskQueue) == 0) {
    pthread_cond_wait(&threadPool->workingCond, &threadPool->threadPoolMutex);
  }

  // 真正的函数执行在这里
  ThreadFunc callback = getFront(taskQueue);
  callback(getArgs(taskQueue));
  printf("the thread id is: %ld\n", pthread_self());
  return NULL;
}

// ----------------------------------------------写法2不太规范的写法展示----------------------------------------------------- //
// 就比如我们想要类比构造函数, 构造函数虽然第一个参数是一个this指针, 然后这里传递是threadpool没有错, 但是在这里如果这样写的话是错误的
// 因为我们在外部进行ThreadPool *threadPool的话, 默认是NULL,
//void createThreadPool(ThreadPool *threadPool, int maxThreads, int minThreads) {
//  threadPool->queueFront = 0;
//  threadPool->queueCapacity = maxThreads;
//
//  // 假设任务队列的和最大的线程数量是有关的, 也就是任务数量不可以超过最大的线程数量
//  threadPool->taskQ = (Task *) malloc(sizeof(Task) * maxThreads);
//  threadPool->workingThreadIDs = (pthread_t *) malloc(sizeof(pthread_t) * maxThreads);
//  for (int i = 0; i < maxThreads; ++i) {
//    /**
//     * 一开始我在想为什么这里不是直接调用任务函数, 而是传递是以worker函数, 不仅仅自己的需求中分析的那样我们需要工作线程
//     * 更是因为我们这里需要的是一个延迟的调用, 这里的worker更像是对真正线程函数的封装.
//     * */
//    pthread_create(&threadPool->workingThreadIDs[i], NULL, worker, threadPool);
//    sleep(3);
//  }
//}
// ----------------------------------------------写法2不太规范的写法展示------------------------------------------------------ //


// ----------------------------------------------正确的写法------------------------------------------------------- //
ThreadPool *createThreadPool(int maxThreads, int minThreads) {
  // 在内部进行初始化
  // 首先我们对threadPool进行初始化:
  ThreadPool *threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));
  TaskQueue *taskQueue = createTaskQueue(maxThreads);

  threadPool->workingThreadIDs = (pthread_t *) malloc(sizeof(pthread_t) * maxThreads);

  pthread_mutex_init(&threadPool->threadPoolMutex, NULL);
  pthread_cond_init(&threadPool->workingCond, NULL);

  for (int i = 0; i < maxThreads; ++i) {
    /**
     * 一开始我在想为什么这里不是直接调用任务函数, 而是传递是以worker函数, 不仅仅自己的需求中分析的那样我们需要工作线程
     * 更是因为我们这里需要的是一个延迟的调用, 这里的worker更像是对真正线程函数的封装.
     * */
    pthread_create(&threadPool->workingThreadIDs[i], NULL, worker, threadPool);
  }
  pthread_create(&threadPool->managerThreadID, NULL, )
  return threadPool;
}
// ----------------------------------------------正确的写法---------------------------------------------------------- //


void destroyThreadPool(ThreadPool *threadPool) {

}



void threadPoolAdd(ThreadPool *threadPool, void *(*taskFunc)(void *), void *arg) {
  // 主要是任务的添加
  TaskQueue *taskQueue = threadPool->taskQueue;
  enQueue(taskQueue, taskFunc); // 任务入队
  setArgs(taskQueue, arg); // 设置参数
}


