//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"
#include "TaskQueue.h"

void *print(void *num) {
  printf("the number is %d\n", *(int*)num);
  return NULL;
}

int main() {
  // 这里错误, 我们没有给threadPool进行初始化, 也就是没有进行给threadPool一个有效的地址, 所以默认是NULL, 那么如果NULL传递进去的话threadPool->属性初始化就是错误的
  ThreadPool *threadPool = createThreadPool(3, 1);
  int num = 2;
  for (int i = 0; i < 2; i++) {
    threadPoolAdd(threadPool, print, &num);
  }
//  printf("the main thread id : %ld\n", pthread_self());
  destroyThreadPool(threadPool);
  return 0;
}