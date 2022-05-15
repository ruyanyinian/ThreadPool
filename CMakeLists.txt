cmake_minimum_required(VERSION 3.10)
project(threadpool)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/bin)
add_library(TaskQueue SHARED TaskQueue.cc ThreadPool.cc)

add_executable(${PROJECT_NAME} main.cc)
target_link_libraries(${PROJECT_NAME} PRIVATE TaskQueue)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(TaskQueue PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})


