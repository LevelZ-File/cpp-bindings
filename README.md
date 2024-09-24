# levelz-cpp

> Header-only C++ Parser & API For LevelZ File Format

![GitHub Release](https://img.shields.io/github/v/release/LevelZ-File/cpp-bindings)

## Overview

Provides C++ bindings for the LevelZ file format. This library is header-only and does not require any additional dependencies.

## Installation

Ensure you have [CMake](https://cmake.org/) installed on your system, then run the following commands:

```bash
# Clone Repo
git clone https://github.com/LevelZ-File/cpp-bindings
cd cpp-bindings

# Build Project, Install with CMake
cmake --build . --config Release --target install

## may require sudo
sudo cmake --build . --config Release --target install
```

## Usage

```cpp
#include <levelz.hpp>

int main() {
    LevelZ::Coordinate2D coord = {0, 0};
    return 0;
}
```

```cpp
#include <levelz.hpp>

using namespace LevelZ;

int main() {
    Level l = parseFile("path/to/file.lvlz")
    return 0;
}
```
