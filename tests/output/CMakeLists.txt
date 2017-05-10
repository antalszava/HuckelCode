cmake_minimum_required(VERSION 3.6)
project(output)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

set(SOURCE_FILES main.cpp MarketMatrixWriter.cpp MarketMatrixWriter.h TestMarketMatrixWriter.cpp TestMarketMatrixWriter.h)
add_executable(output ${SOURCE_FILES})