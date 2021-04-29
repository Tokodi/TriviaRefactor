#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./hash_test.sh <new_output_file>"
    exit 0
fi

ORIGINAL_HASH=d4a26afb9e2939629598194ac6828296229499ed
NEW_HASH="$(sha1sum $1 | awk '{ print $1 }')"

if [ $ORIGINAL_HASH = $NEW_HASH ]; then
    echo "PASSED"
else
    echo ${ORIGINAL_HASH}
    echo ${NEW_HASH}
    echo "FAILED"
fi
