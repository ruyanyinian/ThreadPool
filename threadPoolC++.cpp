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
//  if (pthread_mutex_init(&queueMutex, nullptr) == 0) {
//    printf("the mutex init successful");
//  }
}

TaskQueue::~TaskQueue() {}

void TaskQueue::addTask(const Task &task) {
//  pthread_mutex_lock(&queueMutex);
  taskQueue.push(task);
//  pthread_mutex_unlock(&queueMutex);
}

void TaskQueue::addTask(TaskFunc func, void *args) {
//  pthread_mutex_lock(&queueMutex);
  Task task;
  task.taskFunc = func;
  task.m_args = args;
  taskQueue.push(task);
//  pthread_mutex_unlock(&queueMutex);
}

Task TaskQueue::takeTask() {
//  pthread_mutex_lock(&queueMutex);
  Task &task = taskQueue.front();
  taskQueue.pop(); // 删除元素.
//  pthread_mutex_unlock(&queueMutex);
  return task;
}

size_t TaskQueue::getSize() {
  return taskQueue.size();
}


ThreadPool::ThreadPool(int minThreads, int maxThreads) {
  this->minThreads = minThreads;
  this->maxThreads = maxThreads;
  this->workingNums = 0;
  this->livingNums = minThreads;
  this->killNums = 0;
  shutdown = false;
  tid = new pthread_t[maxThreads]{0};
  taskQueue = new TaskQueue();

  if (pthread_cond_init(&this->notFull, nullptr) !=0 ||
      pthread_cond_init(&this->notEmpty, nullptr) !=0 ||
      pthread_mutex_init(&this->taskQueueMutex, nullptr) != 0) {
    printf("the condition variable init failed!");
  }
  for (int i = 0; i < minThreads; ++i) {  // Note: 一开始就启动最小的线程数量
    pthread_create(&tid[i], nullptr, worker, this); // Note: 这里传递一个this指针
  }
  pthread_create(&mid, nullptr, monitor, this);
}

void *ThreadPool::worker(void *arg) {
  ThreadPool *threadPool = reinterpret_cast<ThreadPool*>(arg);
  TaskQueue *taskQueue = threadPool->taskQueue;
  while (true) {
    pthread_mutex_lock(&threadPool->taskQueueMutex);
    // 判断任务队列是否为空, 如果为空工作线程阻塞
    while (!threadPool->shutdown && taskQueue->getSize() == 0) {
      pthread_cond_wait(&threadPool->notEmpty, &threadPool->taskQueueMutex);
      // 解除阻塞之后是否要销毁线程
      if (threadPool->killNums > 0) {
        threadPool->killNums--;
        if (threadPool->livingNums > threadPool->minThreads) {
          threadPool->livingNums--;
          pthread_mutex_unlock(&threadPool->taskQueueMutex);
          threadPool->killThreads();
        }
      }
    }
    if (threadPool->shutdown) {
      pthread_mutex_unlock(&threadPool->taskQueueMutex);
      threadPool->killThreads();
    }
    // 从任务队列中取出一个任务
    Task task = taskQueue->takeTask();
    threadPool->workingNums++;
    // 线程池解锁
    pthread_mutex_unlock(&threadPool->taskQueueMutex);
    task.taskFunc(task.m_args);
    // 任务处理结束
    pthread_mutex_lock(&threadPool->taskQueueMutex);
    threadPool->workingNums--;
    pthread_mutex_unlock(&threadPool->taskQueueMutex);
  }
  return nullptr;
}

void *ThreadPool::monitor(void *arg) {

  return nullptr;
}

void ThreadPool::killThreads() {
  pthread_t curr_tid = pthread_self();
  for (int i = 0; i < maxThreads; ++i) {
    if (this->tid[i] == curr_tid) {
      std::cout << "start to kill thread: " << pthread_self() << std::endl;
      this->tid[i] = 0;
      break;
    }
  }
  pthread_exit(nullptr);
}

void ThreadPool::threadPoolAdd(Task task) {
  if (shutdown) {
    return;
  }
  // 添加任务，不需要加锁，任务队列中有锁
  taskQueue->addTask(task);
  // 唤醒工作的线程
  pthread_cond_signal(&notEmpty);
}



