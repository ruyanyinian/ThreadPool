cmake_minimum_required(VERSION 3.10)
project(threadpool)
set(CMAKE_CXX_STANDARD 11)
add_executable(${PROJECT_NAME}
        ThreadPool.cc
        main.cc)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

