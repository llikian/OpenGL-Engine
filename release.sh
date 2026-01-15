#!/bin/bash

cmake -B ./build -DCMAKE_BUILD_TYPE=Release\
  && OUTPUT=$(cmake --build build -j)

if [ "$?" -eq 0 ] ; then
    BINARY_FILENAME=$(echo "$OUTPUT" | grep "Built target" | sed -r "s/.*Built target (.*$)/\1/")

    echo -e "\nExecuting program '${BINARY_FILENAME}':\n"
    "bin/$BINARY_FILENAME"
    echo -e "\nProgram exited with code $?\n"
fi
