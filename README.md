[**Introduction**](#introduction) | [**I want my driver now !**](#i-want-my-driver-now) | [**Detailed info**](#detailed-infos) | [**Prerequisites**](#image-prerequisites) | [**Installation**](#image-installation) | [**How-tos**](#image-usage)

# Introduction 



# I want my driver now !
Run these commands
```bash
export DEBIAN_FRONTEND=noninteractive && apt-get install g++ -y -qq git make cmake python python-dev
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git
cd powerboard-driver/
make 
make install
```
This is equivalent to [**Minimal Installation**](#minimal-installation). See [**installation instructions**](#installation-instructions) for details.

# Detailed infos

## User-friendly C++ API

## Python controlled powerboard
There is a Python 3 binding **On top of C++ API**. It exposes C++ functions as a Python module named **pypowerboard**. This makes your powerboards accessibles from within Python CLI and scripts. 

## Containerized development 

# Install from source

```bash
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git
```

This driver comes with a set of addons you may need in your project. This section gives you all instructions to have them on your machine.

## Minimal mode (C++ API)

```bash
# Prerequisites
export DEBIAN_FRONTEND=noninteractive && sudo apt-get install -y -qq g++ make cmake python python-dev
# Build
make
# Install
sudo make install
```

## Python bindings (C++ & Python 3 APIs)

```bash
# Prerequisites
sudo apt-get install -y -qq --no-install-recommends g++ make cmake python python-dev python3 python3-dev python3-pip
# Build
make python
# Install
sudo make install-python
```

## Examples


# Containerized development
- Ubuntu 20.04
  
- Docker (tested with Docker 20.10.7), see [Install Docker Engine](https://docs.docker.com/engine/install/)

- Docker Compose (tested with Docker Compose 1.29.2), see [Install Docker Compose](https://docs.docker.com/compose/install/)
  You may have a `/usr/local/bin/docker-compose: no such file or directory` error. In this case, use
  ```bash
  sudo mkdir /usr/local/bin/docker-compose
  ```
  before restarting the installation process

- Nvidia Container Toolkit (tested with ubuntu20.04 distribution), see [NVIDIA Container Toolkit Installation Guide](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/install-guide.html)

- A PC with GPU. Use the following to list available graphics units
  ```bash
  lshw -c display
  ```

To clone

