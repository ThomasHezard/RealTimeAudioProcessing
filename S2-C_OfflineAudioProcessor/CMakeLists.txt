cmake_minimum_required(VERSION 3.6)
project(OfflineAudioProcessor C CXX)

set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 11)

set(SRCS
        sources/main.cpp
        sources/audio_processor.c)

set(HDRS
        sources/audio_processor.h
        external/AudioFile.h)

add_executable(OfflineAudioProcessor ${SRCS} ${HDRS})
