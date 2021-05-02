#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./hash_test.sh <new_output_file>"
    exit 0
fi

#NOTE: Original hash
#ORIGINAL_HASH=d4a26afb9e2939629598194ac6828296229499ed

#NOTE: Fixed indexing issue in purses, places, inPenaltyBox
#ORIGINAL_HASH=85ca1b50d3115c0ae973c56698c6767ba412b663

#NOTE: Fixed issue that players stuck in penalty box
#ORIGINAL_HASH=31fd0fa900e48ab0454a074e1bc5b6432383bc86

#NOTE: Introduction of Dice class caused new random numbers
#ORIGINAL_HASH=fb6d0876f51d58bc0a01bcbff67606458b8666ad

#NOTE: Refactor of controller's random generator
ORIGINAL_HASH=f5b09ffa87daabf0b39592dbe9da72ce0cd00943
NEW_HASH="$(sha1sum $1 | awk '{ print $1 }')"

if [ $ORIGINAL_HASH = $NEW_HASH ]; then
    echo "PASSED"
else
    echo ${ORIGINAL_HASH}
    echo ${NEW_HASH}
    echo "FAILED"
fi
