CONT_NAME=powerboard-driver-dev-container

# Minimal Mode (C++, No Binding, No Example)
.PHONY: build-minimal
build-minimal:
	rm -rf build/
	rm -rf lib/
	mkdir build/
	make -C thirdparty/libi2c/
	cd build/ && \
	cmake -DBUILD_PYTHON=OFF -DBUILD_EXAMPLES=OFF .. && \
	make --no-print-directory -j4

.PHONY: install
install-minimal:
	cd build/ && \
	make install
	

# Full Mode (C++, Binding, Example)
.PHONY: build-full
build-full:
	rm -rf build/
	rm -rf lib/
	mkdir build/
	make -C thirdparty/libi2c/
	cd build/ && \
	cmake .. && \
	make --no-print-directory -j4

.PHONY: install-full
install-full:
	cd build/ && \
	make install
	python3 setup.py install

# Docker

.PHONY: docker-build
docker-build:
	docker build -f docker/Dockerfile -t lmwafer/powerboard-driver-dev:1.0.0-3 docker/context

.PHONY: up
up:
	docker-compose -f docker/docker-compose.yml up -d
	clear && docker exec -it ${CONT_NAME} bash

.PHONY: down
down:
	docker-compose -f docker/docker-compose.yml down

.PHONY: enter
enter:
	docker exec -it ${CONT_NAME} bash
