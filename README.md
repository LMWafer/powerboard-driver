[**Introduction**](#introduction) | [**I want my driver now !**](#i-want-my-driver-now) | [**Detailed info**](#detailed-infos) | [**Prerequisites**](#image-prerequisites) | [**Installation**](#image-installation) | [**How-tos**](#image-usage)

# Introduction 

<!-- A nice GIF showing Python CLI in action would be cool -->

`powerboard-driver` allows you to pilot powerboards over I2C, from a Single Board Computer (SBC) such as `Jetson Nano` or `Raspberry PI 3`. Ask a motor to turn in a direction, and the powerboard network takes care of everything !

> `powerboard-driver` does not run on a `powerboard`'s MCU, but rather on a SBC. It's task is to interface thesaid SBC with multiple `powerboard-firmware` (i.e. multiple `powerboards`) on the same I2C wire.

This repository hosts code for:
- C++ backbone;
- Python interface;
- Development Docker container;
- Documentation.

- Why this repo



# I want my driver now !
Run these commands
```bash
export DEBIAN_FRONTEND=noninteractive && apt-get install g++ -y -qq git make cmake python python-dev
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git
cd powerboard-driver/
make 
make install
```
This is equivalent to [**Minimal Installation**](#-minimal-mode-(c++)). See [**installation instructions**](#build-from-source) for details.

# Build from source

## Clone with submodules
```bash
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git
```

## Minimal mode (C++)

```bash
# Prerequisites
export DEBIAN_FRONTEND=noninteractive && sudo apt-get install -y g++ make cmake python python-dev
# Build
make
# Install
sudo make install
```

## Full mode (C++ & Python & Examples)

```bash
# Prerequisites
export DEBIAN_FRONTEND=noninteractive && sudo apt-get install -y g++ make cmake python python-dev python3 python3-dev python3-pip
# Build
make build-full
# Install
sudo make install-full
```

# Containerized development

## Perequisites

- Ubuntu 20.04
  
- Docker (tested with Docker 20.10.7), see [Install Docker Engine](https://docs.docker.com/engine/install/)

- Docker Compose (tested with Docker Compose 1.29.2), see [Install Docker Compose](https://docs.docker.com/compose/install/)
  You may have a `/usr/local/bin/docker-compose: no such file or directory` error. In this case, use
  ```bash
  sudo mkdir /usr/local/bin/docker-compose
  ```
  before restarting the installation process

## Get image on your machine

### Download from Dockerhub

```bash
docker pull lmwafer/powerboard-driver-dev
```

### Build from source

```bash
make docker-build
```

## Start a container & open a shell inside

### Provided shortcut

```bash
make up 
make enter
```

### With `Docker`

```bash
docker run -it lmwafer/powerboard-driver-dev \
  --volume /dev:/dev \
  --volume ../:/app/ \
  --name powerboard-driver-dev-container
```

## Stop a running container and remove it

### Provided shortcut

```bash
make down
```

### With `Docker`

```bash
docker stop powerboard-driver-dev-container
docker rm powerboard-driver-dev-container
```