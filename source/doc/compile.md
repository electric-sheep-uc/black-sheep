# Compile

The following is just some basic commands and explanations for how to compile
the code. All of this is to be done within the development environment.

## Setup

First time you build, you will need to generate your `Makefile` with:

    ccmake .

## Build

To be completely safe, you can always rebuild the entire project:

    make clean; make

If you are on a time squeeze, you can also run the faster compilation:

    make

The issue with running only `make` (without `make clean`) is that sometimes
builds will fail as it tries to reuse object files. If there has been a
significant change and it doesn't realize (not supposed to happen, but it still
does) then it can fail in the linking process.

## Settings

You can adjust the compile settings with:

    ccmake .

A few common settings to change:

* `CMAKE_BUILD_TYPE`: `Debug` creates a debug build (that can be used more
easily with `gdb`), `RelWithDebugInfo` is a faster version offering minimal
debug capability, `Release` is the fastest build type which is not easily
debugged.
* `RPI`: `ON` compiles for the robot architecture and `OFF` compiles for the
local architecture.

Any change you need to make to the settings you should also *clean*.

## Clean

Anytime you change the CMake settings you should clean the CMake configuration
and cached files with:

    bash clean.sh
