FROM ubuntu:20.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y -qq --no-install-recommends \
        build-essential \
        cmake \
        python \
        python-dev \
        python3 \
        python3-dev \
        python3-pip
    
WORKDIR /app/
