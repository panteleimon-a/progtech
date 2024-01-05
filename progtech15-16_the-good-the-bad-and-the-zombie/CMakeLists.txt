cmake_minimum_required(VERSION 2.8)
project( NeuralNetwork )

SET (CMAKE_CXX_FLAGS "-fPIC -Wall -std=c++11 -o3 -Wno-sign-compare -fpermissive")

add_executable(the-good-the-bad-and-the-zombie src/characters.cpp)
