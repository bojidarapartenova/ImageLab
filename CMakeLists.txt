cmake_minimum_required(VERSION 3.12)
project(ImageLab)

set(CMAKE_CXX_STANDARD 17)

add_executable(ImageLab 
    main.cpp
    src/String.cpp
    src/ImageManager.cpp
    src/Image.cpp
    src/PBMImage.cpp
    src/PGMImage.cpp
    src/PPMImage.cpp
    src/BlurFilter.cpp
    src/SharpenFilter.cpp
    src/SobelFilter.cpp
    src/ThresholdFilter.cpp
    src/NegativeFilter.cpp
    src/ContrastStretchingFilter.cpp
)

target_include_directories(ImageLab PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/include")