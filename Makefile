CONT_NAME=powerboard-driver-dev-container

# Minimal Mode
minimal:
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
	

# Bindings Mode

python:
	rm -rf build/
	rm -rf lib/
	mkdir build/
	make -C thirdparty/libi2c/
	cd build/ && \
	cmake -DBUILD_PYTHON=ON .. && \
	make --no-print-directory -j4

install-python:
	cd build/ && \
	make install
	python3 setup.py install

# Examples

# Docker

bake:
	python3 baker.py build

up:
	docker-compose -f docker/docker-compose.yml up -d
	clear && docker exec -it ${CONT_NAME} bash

down:
	docker-compose -f docker/docker-compose.yml down

enter:
	docker exec -it ${CONT_NAME} bash
