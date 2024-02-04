cmake_minimum_required(VERSION 3.23)
project(Tetris)

set(CMAKE_CXX_STANDARD 11)
link_libraries(libeasyx.a)

add_executable(Tetris main.cpp Game.cpp Game.hpp Block.hpp Block.cpp)
