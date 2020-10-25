cmake_minimum_required(VERSION 3.17)
project(ch05)

set(CMAKE_CXX_STANDARD 14)
find_package(OpenCV REQUIRED)

add_executable(ch05 main.cpp)
target_link_libraries(ch05 ${OpenCV_LIBS})