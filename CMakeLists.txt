cmake_minimum_required(VERSION 3.8)
project(videoclip_helper)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp)
add_executable(videoclip_helper ${SOURCE_FILES})

find_package(OpenCV REQUIRED)
target_link_libraries(videoclip_helper ${OpenCV_LIBS})