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

  return 0;
}