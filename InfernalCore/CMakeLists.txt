cmake_minimum_required(VERSION 3.10)
project(InfernalCore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- Find Dependencies ---
# We'll use SDL2 for windowing, rendering, and input
find_package(SDL2 REQUIRED)

# --- Add Subdirectories ---
# This will keep our project modular.
# Each subdirectory will have its own CMakeLists.txt
add_subdirectory(src)

# --- Executable ---
# The main executable will be defined in src/CMakeLists.txt 