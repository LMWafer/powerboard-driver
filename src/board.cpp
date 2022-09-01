#include "i2c/i2c.h"
#include "commands.h"
#include "config.h"
#include "board.h"

#include <iostream>
#include <string.h>
#include <unistd.h>
#include <math.h>

using namespace std;

#pragma region Board

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

	// size_4 = 4 * sizeof(unsigned char);
	// size_3 = 3 * sizeof(unsigned char);
	// size_2 = 2 * sizeof(unsigned char);

	memset(&device, 0, sizeof(device));
	device.bus = bus_fd;
	device.addr = address;
	device.page_bytes = 4;
	device.tenbit = 0;
	device.iaddr_bytes = 0;
	device.flags = 0;

	// bridge.owner = this;
	// buck.owner = this;
}

bool Board::arm()
{
	// buffer_2[0] = COMMAND;
	// buffer_2[1] = ARM;
	sendBuffer(unsigned char[] {COMMAND, ARM}, 2 * sizeof(unsigned char));
	return 0;
}

bool Board::disarm()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = DISARM;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t *Board::setSpeedAll(int16_t speed)
{
	speed = correctValue(speed);

	buffer_4[0] = COMMAND;
	buffer_4[1] = SET_SPEED_ALL;
	buffer_4[2] = abs(speed);
	if (!signbit(speed))
		buffer_4[3] = FORWARD;
	else
		buffer_4[3] = BACKWARD;
	sendBuffer(buffer_4, size_4);
	return 0;
}

int16_t Board::setSpeedM1(int16_t speed)
{
	speed = correctValue(speed);

	buffer_4[0] = COMMAND;
	buffer_4[1] = SET_SPEED_M1;
	buffer_4[2] = abs(speed);
	if (!signbit(speed))
		buffer_4[3] = FORWARD;
	else
		buffer_4[3] = BACKWARD;
	sendBuffer(buffer_4, size_4);
	return 0;
}

int16_t Board::setSpeedM2(int16_t speed)
{
	speed = correctValue(speed);

	buffer_4[0] = COMMAND;
	buffer_4[1] = SET_SPEED_M2;
	buffer_4[2] = abs(speed);
	if (!signbit(speed))
		buffer_4[3] = FORWARD;
	else
		buffer_4[3] = BACKWARD;
	sendBuffer(buffer_4, size_4);
	return 0;
}

int16_t *Board::stopAll()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = STOP_ALL;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t Board::stopM1()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = STOP_M1;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t Board::stopM2()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = STOP_M2;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t *Board::brakeAll()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = BRAKE_ALL;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t Board::brakeM1()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = BRAKE_M1;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t Board::brakeM2()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = BRAKE_M2;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t *Board::reverseAll()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = REVERSE_ALL;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t Board::reverseM1()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = REVERSE_M1;
	sendBuffer(buffer_2, size_2);
	return 0;
}

int16_t Board::reverseM2()
{
	buffer_2[0] = COMMAND;
	buffer_2[1] = REVERSE_M2;
	sendBuffer(buffer_2, size_2);
	return 0;
}

#pragma endregion Board

#pragma region Bridge

bool Board::Bridge::enableMA()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = ENABLE_MA;
	owner->sendBuffer(buffer_2, size_2);
	return true;
}

bool Board::Bridge::disableMA()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = DISABLE_MA;
	owner->sendBuffer(buffer_2, size_2);
	return true;
}

bool Board::Bridge::enableMB()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = ENABLE_MB;
	owner->sendBuffer(buffer_2, size_2);
	return true;
}

bool Board::Bridge::disableMB()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = DISABLE_MB;
	owner->sendBuffer(buffer_2, size_2);
	return true;
}

uint8_t Board::Bridge::setSignalIN1(uint8_t setPoint) 
{
	unsigned char *buffer_3 = owner->buffer_3;
	ssize_t size_3 = owner->size_3;
	buffer_3[0] = COMMAND;
	buffer_3[1] = SET_SIGNAL_IN1;
	buffer_3[2] = setPoint;
	owner->sendBuffer(buffer_3, size_3);
	return 0;
}

uint8_t Board::Bridge::setSignalIN2(uint8_t setPoint)
{
	unsigned char *buffer_3 = owner->buffer_3;
	ssize_t size_3 = owner->size_3;
	buffer_3[0] = COMMAND;
	buffer_3[1] = SET_SIGNAL_IN2;
	buffer_3[2] = setPoint;
	owner->sendBuffer(buffer_3, size_3);
	return 0;
}

uint8_t Board::Bridge::setSignalIN3(uint8_t setPoint)
{
	unsigned char *buffer_3 = owner->buffer_3;
	ssize_t size_3 = owner->size_3;
	buffer_3[0] = COMMAND;
	buffer_3[1] = SET_SIGNAL_IN3;
	buffer_3[2] = setPoint;
	owner->sendBuffer(buffer_3, size_3);
	return 0;
}

uint8_t Board::Bridge::setSignalIN4(uint8_t setPoint)
{
	unsigned char *buffer_3 = owner->buffer_3;
	ssize_t size_3 = owner->size_3;
	buffer_3[0] = COMMAND;
	buffer_3[1] = SET_SIGNAL_IN4;
	buffer_3[2] = setPoint;
	owner->sendBuffer(buffer_3, size_3);
	return 0;
}

#pragma endregion Bridge

#pragma region Buck

bool Board::Buck::enableRegulator() 
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = ENABLE_REGULATOR;
	owner->sendBuffer(buffer_2, size_2);
	return 0;
}

bool Board::Buck::disableRegulator()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = DISABLE_REGULATOR;
	owner->sendBuffer(buffer_2, size_2);
	return 0;
}

bool Board::Buck::enableInput()
{
	cout << "Called" << endl;
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	cout << "Copied" << endl;
	buffer_2[0] = COMMAND;
	buffer_2[1] = ENABLE_INPUT;
	cout << "Filled" << endl;
	owner->sendBuffer(buffer_2, size_2);
	cout << "Sent" << endl;
	return 0;
}

bool Board::Buck::disableInput() 
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = DISABLE_INPUT;
	owner->sendBuffer(buffer_2, size_2);
	return 0;
}

bool Board::Buck::enableOutput()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = ENABLE_OUTPUT;
	owner->sendBuffer(buffer_2, size_2);
	return 0;
}

bool Board::Buck::disableOutput()
{
	unsigned char *buffer_2 = owner->buffer_2;
	ssize_t size_2 = owner->size_2;
	buffer_2[0] = COMMAND;
	buffer_2[1] = DISABLE_OUTPUT;
	owner->sendBuffer(buffer_2, size_2);
	return 0;
}

#pragma endregion Buck
