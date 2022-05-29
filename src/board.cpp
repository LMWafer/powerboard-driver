#include "i2c/i2c.h"
#include "commands.h"
#include "board.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <math.h>

using namespace std;

int Board::sendBuffer(unsigned char buffer[], ssize_t size) {
	ssize_t size_sent = i2c_ioctl_write(&device, 0, buffer, size);
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

Board::Board(const unsigned int address, const string &bus_name = "/dev/i2c-1")
{
	int bus_fd;
	const char *bus_name_char = bus_name.c_str();
	if ((bus_fd = i2c_open(bus_name_char)) == -1)
		cout << "An error occured during bus opening..." << endl;

	size_3 = 3 * sizeof(unsigned char);
	size_1 = sizeof(unsigned char);
	
	memset(&device, 0, sizeof(device));
	device.bus = bus_fd;
	device.addr = address;
	device.page_bytes = 3;
	device.tenbit = 0;
	device.iaddr_bytes = 0;
	device.flags = 0;
}

int Board::enable() {
	buffer_1[0] = ENABLE;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::disable() {
	buffer_1[0] = DISABLE;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::setPowerAll(short int power) {
	power = correctValue(power);
	buffer_3[0] = SET_POWER_ALL;
	buffer_3[1] = fabs(power);
	if (signbit(power)) {
		buffer_3[2] = BACKWARD;
	} else {
		buffer_3[2] = FORWARD;
	}
	sendBuffer(buffer_3, size_3);
	return 0;
}

int Board::setPowerM1(short int power) {
	power = correctValue(power);
	buffer_3[0] = SET_POWER_M1;
	buffer_3[1] = fabs(power);
	if (signbit(power)) {
		buffer_3[2] = BACKWARD;
	} else {
		buffer_3[2] = FORWARD;
	}
	sendBuffer(buffer_3, size_3);
	return 0;
}

int Board::setPowerM2(short int power) {
	power = correctValue(power);
	buffer_3[0] = SET_POWER_M2;
	buffer_3[1] = fabs(power);
	if (signbit(power)) {
		buffer_3[2] = BACKWARD;
	} else {
		buffer_3[2] = FORWARD;
	}
	sendBuffer(buffer_3, size_3);
	return 0;
}

int Board::stopAll() {
	buffer_1[0] = STOP_ALL;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::stopM1() {
	buffer_1[0] = STOP_M1;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::stopM2() {
	buffer_1[0] = STOP_M2;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::brakeAll() {
	buffer_1[0] = BRAKE_ALL;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::brakeM1() {
	buffer_1[0] = BRAKE_M1;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::brakeM2() {
	buffer_1[0] = BRAKE_M2;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::reversePowerAll() {
	buffer_1[0] = REVERSE_POWER_ALL;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::reversePowerM1() {
	buffer_1[0] = REVERSE_POWER_M1;
	sendBuffer(buffer_1, size_1);
	return 0;
}

int Board::reversePowerM2() {
	buffer_1[0] = REVERSE_POWER_M2;
	sendBuffer(buffer_1, size_1);
	return 0;
}
