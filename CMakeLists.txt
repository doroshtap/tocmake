cmake_minimum_required(VERSION 3.6)
project(tocmake)

set(CMAKE_CXX_STANDARD 23)
set(SOURCES src/tocmake.cpp
            src/pugixml.cpp
            src/sln_reader.cpp
            src/project_reader.cpp
            src/cmake_generator.cpp)

add_executable(tocmake ${SOURCES})
target_include_directories(tocmake PRIVATE include)
