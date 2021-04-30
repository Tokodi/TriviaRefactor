FROM ubuntu

ENV HOSTNAME dockerhost
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    clang \
    clang-format \
    clang-tidy \
    cmake \
    cppcheck \
    g++ \
    gdb \
    git \
    googletest \
    libgtest-dev \
    make 

# Create and set user
RUN useradd -ms /bin/bash dockeruser
USER dockeruser
WORKDIR /home/dockeruser/
