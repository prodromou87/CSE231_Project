#!/bin/bash

SOURCE_PATH=`pwd`/Passes
OUTPUT_PATH=`pwd`/Output

# MOUNT POINTS IN CONTAINER: 
# --------------------------
#
# SOURCE CODE: /LLVM_ROOT/llvm/lib/Transforms/CSE231_Project
# TESTS: /tests --> Not mounted anymore
# OUTPUT: /output

docker run --rm -it -v ${SOURCE_PATH}:/LLVM_ROOT/llvm/lib/Transforms/CSE231_Project -v ${OUTPUT_PATH}:/output prodromou87/llvm:8 /bin/bash
