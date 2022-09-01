CONT_NAME=powerboard-driver-dev-container

all: build-lib

build-lib:
	rm -rf build/
	rm -rf lib/
	mkdir build/
	make -C thirdparty/libi2c/
	cd build/ && \
	cmake .. && \
	make --no-print-directory -j4

install:
	cd build/ && \
	make install
	python3 setup.py install 

bake-dev:
	python3 baker.py build

up-dev:
	docker-compose -f docker/docker-compose.yml up -d
	clear && docker exec -it ${CONT_NAME} bash

down-dev:
	docker-compose -f docker/docker-compose.yml down

enter-dev:
	docker exec -it ${CONT_NAME} bash
