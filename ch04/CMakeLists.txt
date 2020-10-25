cmake_minimum_required(VERSION 3.17)
project(ch04)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

add_executable(ch04 main.cpp)
target_link_libraries(ch04 ${OpenCV_LIBS})