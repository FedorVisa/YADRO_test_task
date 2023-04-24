cmake_minimum_required(VERSION 3.20)
project(yadro)

set(CMAKE_CXX_STANDARD 20)

add_executable(yadro main.cpp game_club.cpp game_club.h myException.hpp tools.cpp tools.h)