cmake_minimum_required(VERSION 3.23)
project(M3OE-bksoucy)

set(CMAKE_CXX_STANDARD 14)

add_executable(M3OE-bksoucy main.cpp)
target_link_libraries(M3OE-bksoucy -lfreeglut -lglew32 -lopengl32 -lglfw3)

