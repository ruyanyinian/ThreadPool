cmake_minimum_required(VERSION 3.10)
project(threadpool)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c11 -pthread")
add_executable(${PROJECT_NAME}
        ThreadPool.c
        main.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

