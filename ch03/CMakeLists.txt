cmake_minimum_required(VERSION 3.17)
project(ch03)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

add_executable(ch03 main.cpp)
target_link_libraries(ch03 ${OpenCV_LIBS})