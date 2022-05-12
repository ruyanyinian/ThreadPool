//
// Created by qinyu on 2022/5/5.
//

//#include "ThreadPool.h"
#include "TaskQueue.h"

void *print(void *num) {
  printf("the number is %d\n", *(int*)num);
//  printf("the thread id is %ld\n", pthread_self());
  return NULL;
}


int main() {
  TaskQueue *taskQueue = createTaskQueue(100);
//  int *args = (int*)malloc(sizeof(int));
  for (int i = 0; i < 10; i++) {
    int *num = (int*) malloc(sizeof(int)); // NOTE: data是存的是不同的地址的.
    *num = i;
    enTaskQueue(taskQueue, print, num);
  }
  for (int i = 0; i < 10; i++) {

    ThreadFunc f = (ThreadFunc)deTaskFuncQueue(taskQueue);
    f(deArgsQueue(taskQueue));
//    int *ans = (int*)deArgsQueue(taskQueue);
//    printf("the arg is %d\n", *ans);
  }
  return 0;
}