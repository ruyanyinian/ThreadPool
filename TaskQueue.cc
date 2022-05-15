//
// Created by qinyu on 2022/5/7.
//

#include "TaskQueue.h"


Task::Task() {
  m_func = nullptr;
  m_arg = nullptr;
}

Task::Task(callback func, void *arg) {
  m_func = func;
  m_arg = arg;
}

Task::~Task() {

}

TaskQueue::TaskQueue(int capacity) {
    taskQueue = std::queue<Task, 10>(capacity)

}
