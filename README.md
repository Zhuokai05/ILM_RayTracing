# ILM Ray Tracing

## Building

GCC or Clang with C++17 support is required to build this project.

It is reccomended that you use the build script because it adds to its **include path** the vendored dependencies:

- GLM

If you want to **run the build command by hand**, make sure to pass `-isystem vendor -std=c++17` to the compiler.
