//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"



//struct ThreadPool {
//  // threadPool维护一个任务队列
//  Task *taskQ; // 任务队列
//  int queueFront; // 队首
//  int queueRear; // 队尾
//  int queueSize;
//  int queueCapacity;
//
//  // threadPool相关的线程数量
//  int maxThreads;
//  int minThreads;
//  // 线程相关
//  pthread_t *workingThreadIDs, managerThreadID;
//
//  // 互斥锁
//  pthread_mutex_t threadPoolMutex;
//};

// -----------------------------------------------BUG1写法展示-------------------------------------------------------- //
////
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
// -----------------------------------------------BUG1写法展示----------------------------------------------------- //

void *worker(void *arg) {
  // 这里是不是得加上一个条件变量?
  ThreadPool *threadPool = (ThreadPool *)arg;


  threadPool->taskQ[0].func(arg); // 真正的函数执行在这里. 由于这里的func没有初始化所以报错。
  printf("the thread id is: %ld\n", pthread_self());
  return NULL;
}

// ----------------------------------------------写法2不太规范的写法展示----------------------------------------------------- //
// TODO: 这里也写错了, createThreadPool应该是返回的是初始化好的线程池, 我们这里以不应该传递是一个threadpool的.
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
//    pthread_create(&threadPool->workingThreadIDs[i], NULL, worker, threadPool); // TODO:因为这里threadid传入的是一个地址, 所以用不着初始化?
//    sleep(3);
//  }
//}
// ----------------------------------------------写法2不太规范的写法展示------------------------------------------------------ //


// ----------------------------------------------正确的写法------------------------------------------------------- //
ThreadPool *createThreadPool(int maxThreads, int minThreads) {
  // 在内部进行初始化
  // 首先我们对threadPool进行初始化:
  ThreadPool *threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));
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
  return threadPool;
}
// ----------------------------------------------正确的写法---------------------------------------------------------- //


void destroyThreadPool(ThreadPool *threadPool) {

}

void threadPoolAdd(ThreadPool *threadPool, void *(*taskFunc)(void *), void *arg) {
  // 主要是任务的添加
  threadPool->taskQ[0].func = taskFunc;
  threadPool->taskQ[0].arg = arg;

}


