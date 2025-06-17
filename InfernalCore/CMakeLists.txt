cmake_minimum_required(VERSION 3.10)
project(InfernalCore)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependencies
find_package(SDL2 REQUIRED)

# Add third-party libraries
add_subdirectory(vendor/nlohmann_json)

# Define all source files explicitly
set(SOURCES
    "src/game/main.cpp"
    "src/core/Game.cpp"
    "src/core/Log.cpp"
    "src/game/Level.cpp"
    "src/entity/Player.cpp"
    "src/entity/Enemy.cpp"
    "src/input/Input.cpp"
    "src/gfx/TextureManager.cpp"
)

# Define the executable
add_executable(InfernalCore ${SOURCES})

# Link libraries
target_link_libraries(InfernalCore PRIVATE 
    SDL2::SDL2
    /opt/homebrew/lib/libSDL2_image.dylib
    nlohmann_json::nlohmann_json
)

# Define include directories
target_include_directories(InfernalCore PUBLIC
    "${PROJECT_SOURCE_DIR}/include"
    "/opt/homebrew/include"
) 