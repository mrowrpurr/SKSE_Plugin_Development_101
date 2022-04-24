cmake_minimum_required(VERSION 3.21)

project(HelloCpp VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define your program
add_executable(${PROJECT_NAME} main.cpp)

# Add a package from vcpkg (to prove that you setup vcpkg correctly!)
find_path(SIMPLEINI_INCLUDE_DIRS "ConvertUTF.c")
target_include_directories(${PROJECT_NAME} PRIVATE ${SIMPLEINI_INCLUDE_DIRS})
