# Introduction

The initial decision is to use `openscad` [1], a CAD environment that allows
programmers to build models. There are various advantages to this model:

* The models are programmed, utilizing the majority skills of the team
* Output can be viewed at any time, with compiler warnings/errors displayed
* The source code plays nicely with `git` repositories
* Adjustments can be as simple as changing variable values
* Shapes can easily be achieved that could otherwise take a long time by hand
* Plays nicely with Linux, Windows and Mac

# Development Environment

This requires downloading `openscad` [1]. Linux users can get their latest
repository (Debian: `apt-get install openscad`).

Build models with `F6`, render the object with `F5` (in that order).

# Development Process

In general we want to build models that are justified by real measurements and
are adjustable via variables that correctly rely on one another. Improving the
accuracy of some magic value should never break any of the models if built
correctly.

If for example we decide "we want longer legs", this should be as simple as
changing a simple variable, building the models and going straight to print.
For non-experts, making changes to the models should still be very easy and
we'll likely thank ourselves in the future!

In the *future*, we should be able to simulate a robot model and leave it to
decide itself what the best simulated model is for real life performance, to
maximize some behaviour like running speed or weight.

# Building

In a Linux environment, you can run:

    bash run.sh help

This will display some available options, at the time of writing these are
building:

    bash run.sh build

To build the `.stl` files and render the `.png` files (both generated next to
the source). On the other hand, if you just want to build the STL files (which
is faster), run:

    bash run.sh build stl

**NOTE:** Files are put into a directory under `models/stl` for easier copying.
Files are given the format `<NAME>-<GIT_HASH>.stl`, where `<NAME>` is derived
from the OpenCAD filename and `<GIT_HASH>` is the first 8 characters of the
current commit. The purpose is to allow you to easily know where from random
STL files on a memory stick came from and what they are supposed to be.
Therefore, a good workflow is to pre-commit changes before running a build.

And the next option is to clean the directories:

    bash run.sh clean

Removing all binary build files (such as `.stl` and `.png`) files in the
various directories.

# References

[1] [http://www.openscad.org/](http://www.openscad.org/)
