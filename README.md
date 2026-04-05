# AudioViz

A real-time audio spectrum visualizer built with the JUCE framework.

## Requirements

- CMake 3.23.1+
- C++20 compiler
- macOS 10.13+ (x86_64 / arm64)

## Building

Clone the repository with submodules:

```bash
git clone --recurse-submodules git@github.com:GiorgosChr/AudioViz.git
```

Configure and build:

```bash
cmake -S . -B cmake-build-debug -DCMAKE_BUILD_TYPE=Debug
make -C cmake-build-debug -j
```

## Dependencies

- [JUCE](https://github.com/juce-framework/JUCE)
- [cmake-includes](https://github.com/sudara/cmake-includes)
- [melatonin_blur](https://github.com/sudara/melatonin_blur)
