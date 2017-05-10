cmake_minimum_required(VERSION 3.6)
project(tests)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")

set(SOURCE_FILES main.cpp TestMarketMatrixWriter.cpp ../output/MarketMatrixWriter.cpp)
add_executable(tests ${SOURCE_FILES})