cmake_minimum_required(VERSION 3.17)
project(image_processor)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

add_library(contrib_catch_main
        ../../contrib/catch/catch_main.cpp)

target_include_directories(contrib_catch_main
        PUBLIC ../../contrib/catch)


add_executable(image_processor
        image_processor.cpp
        Filter.cpp Image.cpp NegativeFilter.cpp GrayScaleFilter.cpp CropFilter.cpp MatrixFilter.cpp GaussFilter.cpp
        SharpeningFilter.cpp EdgeDetectionFilter.cpp ReadWrite.cpp Parser.cpp ExceptionInFilter.cpp FishEyeFilter.cpp )
