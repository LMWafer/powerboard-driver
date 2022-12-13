[**Introduction**](#introduction) | [**I want my driver now !**](#i-want-my-driver-now) | [**Classic Installation**](#build-from-source) | [**ROS Installation**](#ros-package-build) | [**Docker containers**](#docker-containers)

# Introduction 

<!-- A nice GIF showing Python CLI in action would be cool -->

`powerboard-driver` allows you to pilot powerboards over I2C, from a Single Board Computer (SBC) such as `Jetson Nano` or `Raspberry PI 3`. Ask a motor to turn in a direction, and the powerboard network takes care of everything !

> `powerboard-driver` does not run on a `powerboard`'s MCU, but rather on a computer acting as master for boards. The driver's task is to interface thesaid computer with multiple `powerboard-firmware` (i.e. multiple `powerboards`) on the same I2C wire.

This repository hosts code for:
- C++ backbone;
- Python interface;
- ROS Wrapper;
- Docker container for development;
- Documentation.


# I want my driver now !
Run these commands

```bash
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git
cd powerboard-driver/
make deps-minimal
make
sudo make install
```

This is equivalent to [**Minimal Installation**](#build-from-source): no Python binding, no example, no ROS wrapper.

# Build from source

## Clone with submodules
```bash
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git
cd powerboard-driver/
```

## Minimal mode (C++)

```bash
#-> Prerequisites
make deps-minimal
#-> Build
make
#-> Install
sudo make install
```

## Full mode (C++ & Python & Examples)

```bash
#-> Prerequisites
make deps-full
#-> Build 
make build-full
#-> Install
sudo make install-full
```

# ROS package build 

The following instructions totally replace the above ones. 

> ROS package build has a dedicated process and location, do not perform it on a repo pre-cloned into a random directory.

```bash
#-> Install dependencies
sudo apt-get install -y python3-catkin-tools

#-> Setup  your catkin workspace
mkdir catkin_ws/ && cd catkin_ws/
catkin config --init --mkdirs --extend /opt/ros/<ROS_DISTRO>

#-> Clone with submodules
cd src/
git clone --recurse-submodules https://github.com/LMWafer/powerboard-driver.git

#-> Build the driver in full mode
#-? Run once, library will persist accross catkin builds
make deps-full
make build-full
sudo make install-full
cd ../../

#-> Add other packages
# ...

#-> Build catkin workspace
#-? catkin will recursively look for ROS package into the repo directory, no need to specify path
catkin build
source devel/setup.bash
```

You only need to build the driver once: after that, if needed re-run process from `Build catkin workspace`.

# Docker Containers 

## Containerized Development

### Perequisites

- Ubuntu 20.04
  
- Docker (tested with Docker 20.10.7), see [Install Docker Engine](https://docs.docker.com/engine/install/)

- Docker Compose (tested with Docker Compose 1.29.2), see [Install Docker Compose](https://docs.docker.com/compose/install/)
  You may have a `/usr/local/bin/docker-compose: no such file or directory` error. In this case, use
  ```bash
  sudo mkdir /usr/local/bin/docker-compose
  ```
  before restarting the installation process

### Get image on your machine

Download from Dockerhub

```bash
docker pull lmwafer/powerboard-driver-dev
```

Build from source

```bash
make docker-build
```

### Start a container & open a shell inside

Provided shortcut

```bash
make up 
make enter
```

With `Docker`

```bash
docker run -it lmwafer/powerboard-driver-dev \
  --volume /dev:/dev \
  --volume ../:/ws/ \
  --name powerboard-driver-dev-container && \
docker exec -it powerboard-driver-dev-container bash
```

### Stop a running container and remove it

Provided shortcut

```bash
make down
```

With `Docker`

```bash
docker stop powerboard-driver-dev-container
docker rm powerboard-driver-dev-container
```