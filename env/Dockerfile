FROM ubuntu

ENV HOSTNAME dockerhost
ENV DEBIAN_FRONTEND=noninteractive

# Install required packages
RUN apt-get update && apt-get install -y \
    g++ \
    gdb \
    git \
    make

# Create and set user
RUN useradd -ms /bin/bash dockeruser
USER dockeruser
WORKDIR /home/dockeruser/
