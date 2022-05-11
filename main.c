//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"
#include "TaskQueue.h"

void *print(void *num) {
  printf("the number is %d\n", *(int*)num);
//  printf("the thread id is %ld\n", pthread_self());
  return NULL;
}

typedef struct Person {
  int id;
  const char *name;
}Person;

Person *createPersonObj() {
  Person *pPerson = (Person*) malloc(sizeof(Person));
  pPerson->id = 10;
  pPerson->name = "haha";
  return pPerson;
}


int main() {
  // 这里错误, 我们没有给threadPool进行初始化, 也就是没有进行给threadPool一个有效的地址, 所以默认是NULL, 那么如果NULL传递进去的话threadPool->属性初始化就是错误的
  ThreadPool *threadPool = createThreadPool(1, 1); // NOTE: 如果多线程很难debug的话, 我们可以设置一个线程.
  for (int i = 0; i < 1; i++) {
    int *num = (int*) malloc(sizeof(int));
    *num = i + 100;
    threadPoolAdd(threadPool, print, num);
  }
//  printf("the main thread id : %ld\n", pthread_self());
  destroyThreadPool(threadPool);
  return 0;
}