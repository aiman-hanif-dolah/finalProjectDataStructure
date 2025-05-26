# CMakeLists.txt
cmake_minimum_required(VERSION 3.15)
project(finalProjectDataStructure C)

# Enforce C99 standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Where to find your headers
include_directories(${CMAKE_SOURCE_DIR})

# Define the executable and all its source modules
add_executable(finalProjectDataStructure
        main.c
        data.c
        ui.c
        helpers.c
)
