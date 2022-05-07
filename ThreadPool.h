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

typedef struct ThreadPool ThreadPool;

ThreadPool *createThreadPool(int maxThreads, int minThreads); // threadPool的初始化
void destroyThreadPool(ThreadPool *threadPool);
void threadPoolAdd(ThreadPool *threadPool, void *(*taskFunc)(void *), void *arg);

#endif //THREADPOOL_THREADPOOL_H
