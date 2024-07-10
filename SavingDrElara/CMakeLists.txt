cmake_minimum_required(VERSION 3.26)
project(assignment1)

set(CMAKE_CXX_STANDARD 11)

add_executable(assignment1 main.cpp
        Convolution.cpp
        Convolution.h
        ImageMatrix.cpp
        ImageMatrix.h
        DecodeMessage.cpp
        DecodeMessage.h
        EdgeDetector.cpp
        EdgeDetector.h
        EncodeMessage.cpp
        EncodeMessage.h
        ImageLoader.cpp
        ImageLoader.h
        ImageProcessor.cpp
        ImageProcessor.h
        ImageSharpening.cpp
        ImageSharpening.h
)
