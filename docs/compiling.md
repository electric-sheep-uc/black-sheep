# Compiling

The purpose of this documentation is to get you building our code repository on
a Debian Linux based system.

## Requirements

In a Debian based system (with `apt` available), you will need the following:

    sudo apt-get -y install      \
      build-essential            \
      cmake                      \
      cmake-curses-gui           \
      crossbuild-essential-armhf \
      ditaa                      \
      gcc                        \
      gdb                        \
      g++                        \
      git-lfs                    \
      imagemagick                \
      inkscape                   \
      jq                         \
      libeigen3-dev              \
      libjpeg-dev                \
      libomp-dev                 \
      libv4l-dev                 \
      openscad                   \
      pandoc                     \
      pandoc-citeproc            \
      screen                     \
      socat                      \
      texlive-fonts-recommended  \
      texlive-latex-recommended  \
      v4l-utils                  \
      xvfb
    sudo apt-get -y install  \
      libjpeg-dev:armhf      \
      libv4l-dev:armhf       \
      v4l-utils:armhf

## Building

To build, simply run the following:

    cmake . # Create a Makefile
    make    # Compile using the Makefile

This compiles compiles by default for the Raspberry Pi, to compile for your
local architecture simply run `ccmake .` and switch the `RPI` boolean off.
You'll need to re-run `cmake .`.
