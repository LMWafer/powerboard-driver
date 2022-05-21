#include "i2c/i2c.h"
#include "commands.h"
#include "i2c-nano.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <math.h>

using namespace std;

int Board::sendBuffer() {
	ssize_t size_sent = i2c_ioctl_write(device, 0, buffer, size);
	if (size_sent != size) {
		cout << "Something went wrong during sending" << endl;
		return 1;
	}
	return 0;
}

short int Board::correctValue(short int value) {
	if (value > 254) {
		return 254;
	} else if (value < - 254) {
		return  -254;
	}
}

Board::Board(unsigned int address, const char *bus_name = "/dev/i2c-1")
{
	int bus_fd;
	if ((bus_fd = i2c_open(bus_name)) == -1)
		cout << "An error occured during bus opening..." << endl;

	this->size = 3 * sizeof(unsigned char);
	
	memset(device, 0, sizeof(device));
	device->bus = bus_fd;
	device->addr = address;
	device->page_bytes = 3;
	device->tenbit = 0;
	device->iaddr_bytes = 0;
	device->flags = 0;

	buffer[0] = SET_POWER_ALL;
	buffer[1] = FULL_THROTTLE;
	buffer[2] = 0x00;
	cout << buffer[1] << endl;
	i2c_ioctl_write(device, 0, buffer, size);
	cout << "set power" << endl;
}

int Board::enableBoard() {
	buffer[0] = ENABLE_BOARD;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::disableBoard() {
	buffer[0] = DISABLE_BOARD;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::setPowerAll(short int power) {
	power = correctValue(power);
	cout << "Correct value : " << power << endl;
	buffer[0] = SET_POWER_ALL;
	buffer[1] = fabs(power);
	if (signbit(power)) {
		buffer[2] = BACKWARD;
	} else {
		buffer[2] = FORWARD;
	}
	sendBuffer();
	return 0;
}

int Board::setPowerM1(short int power) {
	power = correctValue(power);
	buffer[0] = SET_POWER_M1;
	buffer[1] = fabs(power);
	if (signbit(power)) {
		buffer[2] = BACKWARD;
	} else {
		buffer[2] = FORWARD;
	}
	sendBuffer();
	return 0;
}

int Board::setPowerM2(short int power) {
	power = correctValue(power);
	buffer[0] = SET_POWER_M2;
	buffer[1] = fabs(power);
	if (signbit(power)) {
		buffer[2] = BACKWARD;
	} else {
		buffer[2] = FORWARD;
	}
	sendBuffer();
	return 0;
}

int Board::stopAll() {
	buffer[0] = STOP_ALL;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::stopM1() {
	buffer[0] = STOP_M1;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::stopM2() {
	buffer[0] = STOP_M2;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::brakeAll() {
	buffer[0] = BRAKE_ALL;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::brakeM1() {
	buffer[0] = BRAKE_M1;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::brakeM2() {
	buffer[0] = BRAKE_M2;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::reversePowerAll() {
	buffer[0] = REVERSE_POWER_ALL;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::reversePowerM1() {
	buffer[0] = REVERSE_POWER_M1;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}

int Board::reversePowerM2() {
	buffer[0] = REVERSE_POWER_M2;
	buffer[1] = 0;
	buffer[2] = 0;
	sendBuffer();
	return 0;
}


int main()
{
	cout << "Hello world !" << endl;
	Board board(0x70);
	board.stopAll();
	usleep(1000000);
	board.setPowerAll(255);
	return 0;
}