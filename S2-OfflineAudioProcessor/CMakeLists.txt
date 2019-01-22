cmake_minimum_required(VERSION 3.6)
project(OfflineAudioProcessor C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SRCS
        main.cpp
        audio_processor.cpp)

set(HDRS
        audio_processor.h)

add_executable(OfflineAudioProcessor ${SRCS} ${HDRS})