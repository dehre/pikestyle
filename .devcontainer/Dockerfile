FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get upgrade -y
RUN apt-get install build-essential -y
RUN apt-get install git -y

#
# Kitware provides these instructions to install the latest CMake version: https://apt.kitware.com/
# Older versions (up to v3.21) don't support C23.
#
RUN apt-get install gpg wget -y
RUN wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | tee /usr/share/keyrings/kitware-archive-keyring.gpg >/dev/null
RUN echo 'deb [signed-by=/usr/share/keyrings/kitware-archive-keyring.gpg] https://apt.kitware.com/ubuntu/ focal main' | tee /etc/apt/sources.list.d/kitware.list >/dev/null
RUN apt-get update
RUN rm /usr/share/keyrings/kitware-archive-keyring.gpg
RUN apt-get install kitware-archive-keyring -y
RUN apt-get install cmake -y

RUN apt-get install clang-tidy -y
RUN apt-get install valgrind strace ltrace -y
RUN apt-get install man -y
RUN yes | unminimize
