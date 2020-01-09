SRC_DIR := $(abspath $(dir $(lastword $(MAKEFILE_LIST)))../)

build:
	docker build -t ubuntu_clang_image .
	- docker rm ubuntu_clang
	docker run -it -v $(SRC_DIR):/src --name ubuntu_clang  ubuntu_clang_image /bin/bash

ls:
	docker image ls

start:
	docker start -ia ubuntu_clang
