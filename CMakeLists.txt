cmake_minimum_required(VERSION 3.17)
project(11_ex5_314670274)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(11_ex5_314670274
        DataStructFile.cpp
        DataStructFile.h
        File.cpp
        File.h
        FileCharProxy.h
        Main.cpp
        System.cpp
        System.h)
