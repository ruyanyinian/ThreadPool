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
  // bug: 当maxthread = 2, 并且只有一个task 添加到队列中的时候, 程序不知道阻塞到哪里了.
  printf("the main thread id is %ld\n", pthread_self());
  int *num[10] = {};
  ThreadPool *threadPool = createThreadPool(5, 1);

  for (int i = 0; i < 5; i++) {
    num[i] = (int*) malloc(sizeof(int));
    *num[i] = i;
    threadPoolAdd(threadPool, print, num[i]);
  }
  sleep(15);
  destroyThreadPool(threadPool); // 析构
  for (int i = 0; i < 10; i++) {
    if (num[i]) {
      free(num[i]);
      num[i] = NULL;
    }

  }
  return 0;
}