//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"
//#include "TaskQueue.h"

void *print(void *num) {
  printf("the number is %d\n", *(int*)num);
  return NULL;
}


int main() {
  printf("the main thread id is %ld\n", pthread_self());
  int *num[10] = {};
  ThreadPool *threadPool = createThreadPool(1, 1);

  for (int i = 0; i < 1; i++) {
    num[i] = (int*) malloc(sizeof(int));
    *num[i] = i;
    threadPoolAdd(threadPool, print, num[i]);
  }
  sleep(1);


  destroyThreadPool(threadPool); // 析构
  for (int i = 0; i < 2; i++) {
    if (num[i]) {
      free(num[i]);
      num[i] = NULL;
    }

  }
  return 0;
}