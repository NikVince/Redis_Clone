cmake_minimum_required(VERSION 3.28)
project(Redis_Clone)
set(CMAKE_CXX_STANDARD 20)

# Add the source directory to include path
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# Define the source files
set(SOURCES
    src/main.cpp
)

# Create the executable from the source files
add_executable(Redis_Clone ${SOURCES})