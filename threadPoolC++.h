//
// Created by qinyu on 2022/5/17.
//

#ifndef THREADPOOL_THREADPOOLC_H
#define THREADPOOL_THREADPOOLC_H
#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include <queue>

using namespace std;
typedef void*(*TaskFunc)(void*);

struct Task {
public:
  Task();
  Task(TaskFunc func, void *args);
  ~Task();

public:
  TaskFunc taskFunc;
  void *m_args;
};


struct TaskQueue {
public:
  TaskQueue();
  ~TaskQueue();
public:
  void addTask(const Task &task); // Note: 这里只是少调用一次拷贝而已
  void addTask(TaskFunc func, void *args);
  Task takeTask();
  std::size_t getSize();
private:
  std::queue<Task> taskQueue;
  pthread_mutex_t queueMutex;
};

class ThreadPool {

public:
  ThreadPool();
  ThreadPool(int minThreads, int maxThreads);

public:
  static void *worker(void *);
  static void *monitor(void *);
  void threadPoolAdd();

private:
  pthread_t *tid, mid;
  pthread_cond_t notFull, notEmpty;
  bool shutdown;
  int killNums, maxThreads, minThreads, livingNums, workingNums;
};
#endif //THREADPOOL_THREADPOOLC_H
