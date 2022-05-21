all: clean i2c-nano run

clean:
	rm -rf build/*

# i2c-nano.o:
# 	cd build/ && cmake .. && make

i2c-nano: src/i2c-nano.cpp
	cd src/ && g++ i2c-nano.cpp -Wall -g -I../thirdparty/libi2c/include -o ../build/i2c-nano.o -li2c

run: 
	cd build/ && ./i2c-nano.o