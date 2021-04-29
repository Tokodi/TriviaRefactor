#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./hash_test.sh <new_output_file>"
    exit 0
fi

ORIGINAL_HASH=85ca1b50d3115c0ae973c56698c6767ba412b663
NEW_HASH="$(sha1sum $1 | awk '{ print $1 }')"

if [ $ORIGINAL_HASH = $NEW_HASH ]; then
    echo "PASSED"
else
    echo ${ORIGINAL_HASH}
    echo ${NEW_HASH}
    echo "FAILED"
fi
