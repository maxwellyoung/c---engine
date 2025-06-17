# Infernal Engine

This is the C++ game engine powering "Infernal Ascent", a 2D platformer micro-Metroidvania. The game's core concept involves descending through the circles of Hell, losing abilities along the way and mastering movement with a dwindling skillset.

This repository contains the engine source code. The game itself is being developed alongside the engine.

## Design Philosophy

The engine is being built with the following principles in mind, as laid out in the [design document](docs/INFERNAL_ASCENT_DESIGN.md):

- **Tactile Purity:** Responsive, 60fps-locked controls.
- **Minimalism:** Simple, focused codebase. Using libraries like SDL2 for low-level access.
- **Data-Driven:** Game data like level layouts are loaded from external files (e.g., JSON).

## Getting Started

### Prerequisites

- **C++17 Compiler:** A modern C++ compiler (GCC, Clang, MSVC).
- **CMake:** Version 3.10 or newer.
- **Ninja:** (Recommended) For faster builds.
- **SDL2 & SDL2_image:** The core libraries for windowing, input, and graphics.

#### Installation on macOS (with Homebrew)

```bash
brew install cmake ninja sdl2 sdl2_image
```

#### Installation on Ubuntu/Debian

```bash
sudo apt-get update
sudo apt-get install cmake ninja-build libsdl2-dev libsdl2-image-dev
```

### Building

1.  **Clone the repository:**

    This project uses Git submodules for some dependencies. Clone the repository recursively to get them:

    ```bash
    git clone --recursive https://github.com/maxwell-young/c--engine.git
    cd c--engine
    ```

    If you've already cloned the repository without the `--recursive` flag, you can initialize the submodules with:

    ```bash
    git submodule update --init --recursive
    ```

2.  **Configure with CMake:**

    Create a build directory and run CMake. Using the Ninja generator is recommended.

    ```bash
    mkdir build
    cd build
    cmake .. -G Ninja
    ```

    _Note for macOS users:_ The `CMakeLists.txt` is configured to find SDL2 installed via Homebrew on Apple Silicon (`/opt/homebrew`). If you have it installed elsewhere, you may need to adjust the `CMAKE_MODULE_PATH` in `InfernalCore/CMakeLists.txt`.

3.  **Build the project:**

    Run Ninja (or Make) to build the executable.

    ```bash
    ninja
    ```

    Or, if you didn't use the Ninja generator:

    ```bash
    make
    ```

### Running

After a successful build, the executable will be located in the `build/bin/` directory.

```bash
./bin/InfernalCore
```
