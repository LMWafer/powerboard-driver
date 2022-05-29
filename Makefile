IMAGE_NAME=lmwafer/jetson-i2c-powerboard
DEV_IMAGE_TAG=dev-0.2-ubtunu20.04
DEV_CONT_NAME=jetson-i2c-powerboard-dev-container

all: build-lib

build-lib:
	mkdir build/
	cd build/ && \
	cmake .. && \
	make --no-print-directory -j4 && \
	sudo make install
	sudo python3 setup.py install || \
	rm -rf build/

bake-dev:
	docker build -t ${IMAGE_NAME}:${DEV_IMAGE_TAG} -f docker/dev_container/Dockerfile .

up-dev:
	docker-compose -f docker/dev_container/docker-compose.yml up -d
	clear && docker exec -it ${DEV_CONT_NAME} bash

down-dev:
	docker-compose -f docker/dev_container/docker-compose.yml down

enter-dev:
	docker exec -it ${DEV_CONT_NAME} bash
