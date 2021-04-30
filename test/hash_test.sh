#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./hash_test.sh <new_output_file>"
    exit 0
fi

#NOTE: Fixed indexing issue in purses, places, inPenaltyBox
#ORIGINAL_HASH=d4a26afb9e2939629598194ac6828296229499ed

#NOTE: Fixed issue that players stuck in penalty box
#ORIGINAL_HASH=85ca1b50d3115c0ae973c56698c6767ba412b663

ORIGINAL_HASH=31fd0fa900e48ab0454a074e1bc5b6432383bc86
NEW_HASH="$(sha1sum $1 | awk '{ print $1 }')"

if [ $ORIGINAL_HASH = $NEW_HASH ]; then
    echo "PASSED"
else
    echo ${ORIGINAL_HASH}
    echo ${NEW_HASH}
    echo "FAILED"
fi
