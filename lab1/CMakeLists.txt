cmake_minimum_required(VERSION 3.10)
project(lab1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCES
    src/LRU.cpp
    src/LFU.cpp
    src/CounterFibonachi.cpp
)

set(HEADERS
    src/LRU.h
    src/LFU.h
    src/CounterFibonachi.h
    src/ICacheable.h
)

# Создаём статическую библиотеку lab1_lib из SOURCES HEADERS)
add_library(${PROJECT_NAME}_lib STATIC
    ${SOURCES}
    ${HEADERS}
)

# Создаём исполняемый файл lab1_run на основе main.cpp
add_executable(${PROJECT_NAME}_run src/main.cpp)

target_include_directories(${PROJECT_NAME}_run PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(${PROJECT_NAME}_run PRIVATE
    ${PROJECT_NAME}_lib
)

