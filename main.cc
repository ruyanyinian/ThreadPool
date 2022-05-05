//
// Created by qinyu on 2022/5/5.
//

#include "ThreadPool.h"


int main() {
  // 这里错误, 我们没有给threadPool进行初始化, 也就是没有进行给threadPool一个有效的地址, 所以默认是NULL, 那么如果NULL传递进去的话threadPool->属性初始化就是错误的
  // todo(qinyu) 没有给threadPool初始化, 默认是NULL
//  ThreadPool* threadPool;


//  bug:nvalid application of 'sizeof' to an incomplete type 'ThreadPool', 这是因为struct ThreadPool定义在源文件中
//  ThreadPool* threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));

//  如果避免不完整的类型, 我们必须把这个ThreadPool这个结构体类型进行对外暴漏. 比如我们现在放到头文件里面, 然后我们Include这个头文件, 编译器就知道完整的类型了
// 但是这样的话, 我们的taskQ结构体也暴漏在外面了
  ThreadPool *threadPool = (ThreadPool *) malloc(sizeof(ThreadPool));
  createThreadPool(threadPool, 1, 1);
  return 0;
};