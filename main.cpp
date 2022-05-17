//
// Created by qinyu on 2022/5/5.
//

#include "threadPoolC++.h"
//#include "TaskQueue.h"

void *print(void *num) {
  printf("the number is %d\n", *(int*)num);
}


int main() {
  // bug: 当maxthread = 2, 并且只有一个task 添加到队列中的时候, 程序不知道阻塞到哪里了.
//  printf("the main thread id is %ld\n", pthread_self());
//  int *num[10] = {};
//  ThreadPool *threadPool = createThreadPool(5, 3);
//
//  for (int i = 0; i < 5; i++) {
//    num[i] = (int*) malloc(sizeof(int));
//    *num[i] = i;
//    threadPoolAdd(threadPool, print, num[i]);
//  }
//  sleep(5);
//  destroyThreadPool(threadPool); // 析构
//  for (int i = 0; i < 10; i++) {
//    if (num[i]) {
//      free(num[i]);
//      num[i] = NULL;
//    }
//  }

  TaskQueue taskQueue;
  int *num = new int(5);
  taskQueue.addTask(print, num);
  Task task = taskQueue.takeTask();
//  task.taskFunc
  printf("the size is %ld", taskQueue.getSize());

  return 0;
}