//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"

void* print(void *num) {
  printf("the number is %d", *(int*)num);
  return NULL;
}


int main() {
  // 这里错误, 我们没有给threadPool进行初始化, 也就是没有进行给threadPool一个有效的地址, 所以默认是NULL, 那么如果NULL传递进去的话threadPool->属性初始化就是错误的
  // todo(qinyu) 没有给threadPool初始化, 默认是NULL
  // 1. ThreadPool threadPool;
  // 2. ThreadPool *threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));
  ThreadPool *threadPool = createThreadPool(1, 1);
  int num = 19;
  for (int i = 0; i < 1; i++) {
    threadPoolAdd(threadPool, print, &num);
  }
  return 0;
}