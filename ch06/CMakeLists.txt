cmake_minimum_required(VERSION 3.17)
project(ch06)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

add_executable(ch06 main.cpp)
target_link_libraries(ch06 ${OpenCV_LIBS})