cmake_minimum_required(VERSION 3.28)
project(color)

set(CMAKE_CXX_STANDARD 23)
find_package(X11 REQUIRED)

include_directories(${X11_INCLUDE_DIR})

add_executable(color main.cpp)
target_link_libraries(color ${X11_LIBRARIES} -lXtst)