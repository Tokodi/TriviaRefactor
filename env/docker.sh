#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Usage: ./docker.sh <container_name>"
    exit 0
fi

IMAGE_NAME=$1

docker run                                  \
    -ti                                     \
    -v $HOME:/home/dockeruser               \
    ${IMAGE_NAME}                           \
    bash
