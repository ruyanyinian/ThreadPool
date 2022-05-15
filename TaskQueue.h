//
// Created by qinyu on 2022/5/7.
//

#ifndef THREADPOOL_TASKQUEUE_H
#define THREADPOOL_TASKQUEUE_H
#include <queue>
#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 100
#define ERROR -99 // 一般来说我们定义一个
#define CORRECT 0

typedef void(*callback)(void*);
using namespace std;

struct Task {
public:
  Task();
  Task(callback func, void *arg);
  ~Task();

private:
  callback m_func;
  void *m_arg;
};

class TaskQueue {
public:
  TaskQueue() {};
  TaskQueue(int capacity);
  TaskQueue(const TaskQueue &taskQueue);
  TaskQueue(TaskQueue &&taskQueue);
  void enTaskQueue(Task &task);
  void enTaskQueue()
  Task deTaskQueue();
  int getSize();
  int getCapacity();
  ~TaskQueue();
private:
  std::queue<Task> taskQueue;
  int capacity;
};
#endif //THREADPOOL_TASKQUEUE_H
