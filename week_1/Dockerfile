# Dockerfile with C++ tools for ECEP520 Wintero 2020
# Instructor/maintainer: Eric Klavins
# To build: docker build -t cpp . 
# To start: docker run -v your_path:/source -it cpp bash

FROM gcc

RUN apt-get update && \
    apt-get install -y git && \
    apt-get install -y cmake && \
    apt-get install -y cppcheck && \
    apt-get install -y graphviz && \
    apt-get install -y doxygen && \
    apt-get install -y nano && \
    apt-get install -y nodejs 

# Build google test
WORKDIR /usr/src
RUN git clone https://github.com/google/googletest.git
WORKDIR /usr/src/googletest/install
RUN cmake ../ && make && make install

# Install json.h
RUN mkdir /usr/local/include/json
WORKDIR /usr/local/include/json
RUN curl -O -J -L https://github.com/nlohmann/json/releases/download/v3.5.0/json.hpp
RUN mv json.hpp json.h

# Install httplib
WORKDIR /tmp
RUN git clone https://github.com/klavins/cpp-httplib.git
RUN mkdir /usr/local/include/httplib
RUN mv /tmp/cpp-httplib/httplib.h /usr/local/include/httplib
RUN rm -r /tmp/cpp-httplib

# Install ws to serve a website
RUN curl https://www.npmjs.com/install.sh | sh
RUN npm install -g local-web-server

# Install uSockets
WORKDIR /tmp
RUN git clone https://github.com/uNetworking/uSockets.git
WORKDIR /tmp/uSockets
RUN make
RUN mv src /usr/local/include/uSockets
RUN mv uSockets.a /usr/local/lib/libuSockets.a
RUN rm -r /tmp/uSockets

# Install uWebSockets
WORKDIR /tmp
RUN git clone https://github.com/uNetworking/uWebSockets.git
RUN mv /tmp/uWebSockets/src /usr/local/include/uWebSockets
RUN rm -r /tmp/uWebSockets

# Get ready to write some code
RUN mkdir /source
WORKDIR /source

