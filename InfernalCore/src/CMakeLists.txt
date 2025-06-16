# --- Source Files ---
# We'll glob for all .cpp files in our source directories for now.
# For larger projects, explicitly listing files is better for performance.
file(GLOB_RECURSE SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
)

# --- Executable ---
add_executable(InfernalCore ${SOURCES})

# --- Link Libraries ---
# Link SDL2 to our executable
target_link_libraries(InfernalCore PRIVATE SDL2::SDL2)

# --- Include Directories ---
# So we can use #include "core/..."
target_include_directories(InfernalCore PUBLIC
    "${PROJECT_SOURCE_DIR}/src"
    "${PROJECT_SOURCE_DIR}/include"
    ${SDL2_INCLUDE_DIRS}
) 