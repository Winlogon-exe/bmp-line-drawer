cmake_minimum_required(VERSION 3.28)
project(zadanie)

set(CMAKE_CXX_STANDARD 20)

set(HEADERS
    inc/BMPViewer.h
)

set(SOURCES
    src/main.cpp
    src/BMPViewer.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/inc)
