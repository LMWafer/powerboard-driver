FROM ubuntu:20.04

RUN apt-get update && \
    apt-get upgrade -y && \
    apt-get install -y -qq --no-install-recommends \
        build-essential \
        make \
        nano
    
WORKDIR /dpds/jetson_i2c_powerboard/
