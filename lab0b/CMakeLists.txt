cmake_minimum_required(VERSION 3.10)
project(lab0b)

set(CMAKE_CXX_STANDARD 11)

# Указываем исходные файлы
set(SOURCES
    main.cpp
    App.cpp
    reader.cpp
    spliter.cpp
    counter.cpp
    writer.cpp
)

# Создаем исполняемый файл
add_executable(lab0b ${SOURCES})