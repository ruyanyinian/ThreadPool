//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"
// todo: 为什么这里的参数必须是void, 导致我们在函数里面还得转类型
// 这是因为threadPoolAdd函数的第二个参数必须是void*(*func)(void*)类型的.
// 函数指针变量在传递参数的时候必须是类型一致的

void* print(void *num) {
  printf("the number is %d", *(int*)num);
  return NULL;
}


int *haha(int *num) {
  printf("the num is : %d\n", *num);
  return num;
}

void callback(void *(* func1)(void *), void *arg) {
  func1(arg);
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
  printf("the main thread id : %ld\n", pthread_self());
  return 0;
}