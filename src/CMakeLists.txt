cmake_minimum_required(VERSION 3.10)

project(mtfind VERSION 1.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(MtfindConfig.h.in MtfindConfig.h)

add_executable(mtfind 
               main.cpp
               SearchTaskQueue.cpp
               LinesReader.cpp
               LinesReaderThread.cpp
               WorkerThread.cpp
               InputParametersReader.cpp
               Report.cpp)

target_include_directories(mtfind PUBLIC "${PROJECT_BINARY_DIR}")

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(mtfind PRIVATE Threads::Threads)


