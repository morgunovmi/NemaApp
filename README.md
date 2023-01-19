# NemaApp

## Introduction

GUI application for controlling stepper motors through COM ports

## Usage
### Prerequisites

If you just need the app, you can download it on
the Releases page. To run it you'll need Visual C++ Redistributable installed on your PC.

## Build

These build instructions are for a release build and assume you have Cmake installed, have vcpkg in path-to-vcpkg,
and running x64-windows. Adjust accordingly.

```
git clone --recurse-submodules -j8 https://github.com/morgunovmi/NemaApp.git
cd NemaApp
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=path-to-vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..
cmake --build . --config=Release
..\bin\Release\App.exe
```
