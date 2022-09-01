#include "i2c/i2c.h"
#include "commands.h"
#include "config.h"
#include "board.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <math.h>

using namespace std;

int Board::sendBuffer(unsigned char buffer[], ssize_t size)
{
	ssize_t size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
	{
		cout << "Something went wrong during sending" << endl;
		return 1;
	}
	return 0;
}

int16_t Board::correctValue(int16_t value)
{
	value = value <= 254 ? value : 254;
	value = value >= -254 ? value : -254;
	return value;
}

Board::Board(const uint8_t address, const string &bus_name = "/dev/i2c-1")
{
	int bus_fd;
	const char *bus_name_char = bus_name.c_str();
	if ((bus_fd = i2c_open(bus_name_char)) == -1)
		cout << "An error occured during bus opening..." << endl;

	memset(&device, 0, sizeof(device));
	device.bus = bus_fd;
	device.addr = address;
	device.page_bytes = 4;
	device.tenbit = 0;
	device.iaddr_bytes = 0;
	device.flags = 0;
}

bool Board::arm()
{
	unsigned char buffer[2] = {COMMAND, ARM};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

bool Board::disarm()
{
	unsigned char buffer[2] = {COMMAND, DISARM};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t *Board::setSpeedAll(int16_t speed)
{
	speed = correctValue(speed);
	unsigned char buffer[4] = {COMMAND, SET_SPEED_ALL, abs(speed), 0};
	if (!signbit(speed))
		buffer[3] = FORWARD;
	else
		buffer[3] = BACKWARD;
	sendBuffer(buffer, 4 * sizeof(unsigned char));
	return 0;
}

int16_t Board::setSpeedM1(int16_t speed)
{
	speed = correctValue(speed);
	unsigned char buffer[4] = {COMMAND, SET_SPEED_M1, abs(speed), 0};
	if (!signbit(speed))
		buffer[3] = FORWARD;
	else
		buffer[3] = BACKWARD;
	sendBuffer(buffer, 4 * sizeof(unsigned char));
	return 0;
}

int16_t Board::setSpeedM2(int16_t speed)
{
	speed = correctValue(speed);
	unsigned char buffer[4] = {COMMAND, SET_SPEED_M2, abs(speed), 0};
	if (!signbit(speed))
		buffer[3] = FORWARD;
	else
		buffer[3] = BACKWARD;
	sendBuffer(buffer, 4 * sizeof(unsigned char));
	return 0;
}

int16_t *Board::stopAll()
{
	unsigned char buffer[2] = {COMMAND, STOP_ALL};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t Board::stopM1()
{
	unsigned char buffer[2] = {COMMAND, STOP_M1};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t Board::stopM2()
{
	unsigned char buffer[2] = {COMMAND, STOP_M2};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t *Board::brakeAll()
{
	unsigned char buffer[2] = {COMMAND, BRAKE_ALL};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t Board::brakeM1()
{
	unsigned char buffer[2] = {COMMAND, BRAKE_M1};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t Board::brakeM2()
{
	unsigned char buffer[2] = {COMMAND, BRAKE_M2};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t *Board::reverseAll()
{
	unsigned char buffer[2] = {COMMAND, REVERSE_ALL};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t Board::reverseM1()
{
	unsigned char buffer[2] = {COMMAND, REVERSE_M1};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}

int16_t Board::reverseM2()
{
	unsigned char buffer[2] = {COMMAND, REVERSE_M2};
	sendBuffer(buffer, 2 * sizeof(unsigned char));
	return 0;
}
