# Created by:   VPR
# Created:      March 6th, 2025

# Updated by:   VPR
# Updated:      March 6th, 2025

FROM ubuntu:22.04

# Set env to avoid user input interruption during installation
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && echo $TZ > /etc/timezone

# Install required packages
RUN apt-get update && apt upgrade -y
RUN apt-get install -y --no-install-recommends \
    wget \
    curl \
    ca-certificates \
    build-essential \
    cmake \
    nasm \
    mingw-w64
RUN update-ca-certificates

# Create working environment
WORKDIR /opt/anti-debugging

# Copy sources
COPY CMakeLists.txt CMakeLists.txt
COPY Makefile Makefile
COPY mingw-toolchain.cmake mingw-toolchain.cmake

# Set docker user to local user uid:gid
ARG LOCAL_USER
ARG LOCAL_UID
ARG LOCAL_GID

RUN chown -R $LOCAL_UID:$LOCAL_GID /opt/anti-debugging

# Install testing suite

# Become user
USER $LOCAL_USER
ENV HOME=/home/$LOCAL_USER
