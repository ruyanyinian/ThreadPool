//
// Created by qinyu on 2022/5/17.
//

#include "threadPoolC++.h"

Task::Task() {
  taskFunc = nullptr;
  m_args = nullptr;
}

Task::Task(TaskFunc func, void *args) {
  taskFunc = func;
  m_args = args;
}

Task::~Task() {}

TaskQueue::TaskQueue() {
  if (pthread_mutex_init(&queueMutex, nullptr) == 0) {
    printf("the mutex init successful");
  }
}

TaskQueue::~TaskQueue() {}

void TaskQueue::addTask(const Task &task) {
  pthread_mutex_lock(&queueMutex);
  taskQueue.push(task);
  pthread_mutex_unlock(&queueMutex);
}

void TaskQueue::addTask(TaskFunc func, void *args) {
  pthread_mutex_lock(&queueMutex);
  Task task;
  task.taskFunc = func;
  task.m_args = args;
  taskQueue.push(task);
  pthread_mutex_unlock(&queueMutex);
}

Task TaskQueue::takeTask() {
  pthread_mutex_lock(&queueMutex);
  Task &task = taskQueue.front();
  taskQueue.pop(); // 删除元素.
  pthread_mutex_unlock(&queueMutex);
  return task;
}

size_t TaskQueue::getSize() {
  return taskQueue.size();
}

ThreadPool::ThreadPool(int minThreads, int maxThreads) {
  this->minThreads = minThreads;
  this->maxThreads = maxThreads;
  shutdown = false;
  tid = new pthread_t[maxThreads]{0};

  if (pthread_cond_init(&this->notFull, nullptr) !=0 ||
      pthread_cond_init(&this->notEmpty, nullptr) !=0 ) {
    printf("the condition variable init failed!");
  }
  for (int i = 0; i < minThreads; ++i) {  // Note: 一开始就启动最小的线程数量
    pthread_create(&tid[i], nullptr, worker, this); // Note: 这里传递一个this指针
  }
  pthread_create(&mid, nullptr, monitor, this);
}

void *ThreadPool::worker(void *arg) {
  ThreadPool *threadPool = reinterpret_cast<ThreadPool*>(arg);

  return nullptr;
}

void *ThreadPool::monitor(void *arg) {

  return nullptr;
}


void ThreadPool::threadPoolAdd() {

}



