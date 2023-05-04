#!/bin/bash

echo "BUILD TIME LINKING"
# compile showing where shared library is at build time (FAIL linking at runtime)
clang sorting_plot.c -L . -lsorting

echo "RUNTIME LINKING"
# compile showing where shared library is at runtime time (FAIL linking at build time)
clang sorting_plot.c -Wl,-rpath,. -lsorting

echo "RUNTIME AND BUILD TIME LINKING"
# compile showing where shared library is at runtime and build time (SUCCESS)
clang sorting_plot.c -Wl,-rpath,. -L . -lsorting
