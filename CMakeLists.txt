cmake_minimum_required(VERSION 3.16.3)

set(CMAKE_CXX_FLAGS "-O3 -Wall -Wextra")

# project name
project(izhikevich)

# set the C++20 standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# cmake enable AVX
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")

include(CheckIncludeFileCXX)
include(CheckCXXCompilerFlag)

# creates the variable EXEC
set(IZHIKEVICH_EXEC izhikevich)

# include
include_directories(include)

# add the files of the executables
file(GLOB IZHIKEVICH_SOURCE src/izhikevich.cpp)

# add hebb and perceptron as libraries
file(GLOB LIB_SOURCES lib/*.cpp)
file(GLOB LIB_HEADERS include/*.hpp)

# add_compile_options(-pthread)
find_package(Threads REQUIRED)

# opencv
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

# compile executables
add_executable(${IZHIKEVICH_EXEC} ${IZHIKEVICH_SOURCE})

# shared libraries pthreads
target_link_libraries(${IZHIKEVICH_EXEC} ${CMAKE_THREAD_LIBS_INIT})

# shared libraries opencv
target_link_libraries(${IZHIKEVICH_EXEC} ${OpenCV_LIBS})

