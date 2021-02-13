cmake_minimum_required(VERSION 3.17)
project(LMS)

set(CMAKE_CXX_STANDARD 14)

add_executable(LMS main.cpp Student.cpp Student.h LMS.cpp LMS.h)