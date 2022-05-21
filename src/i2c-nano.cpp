#include "i2c/i2c.h"
#include "commands.h"

#include <string.h>
#include <iostream>
#include <unistd.h>

using namespace std;

int main()
{
	cout << "Hello world !" << endl;

	int bus;

	/* Open i2c bus /dev/i2c-0 */
	if ((bus = i2c_open("/dev/i2c-1")) == -1)
	{
		cout << "An error occured during bus opening..." << endl;
	}

	I2CDevice device;
	memset(&device, 0, sizeof(device));

	device.bus = bus;
	device.addr = 0x70;
	device.page_bytes = 3;
	device.tenbit = 0;
	device.iaddr_bytes = 0;
	device.flags = 0;

	unsigned int micro(1000000);

	ssize_t size = 3 * sizeof(unsigned char);
	unsigned char buffer[3] = {STOP_ALL, 0, 0};

	// buffer[0] = SET_POWER_ALL;
	// buffer[1] = FULL_THROTTLE;
	// buffer[2] = FORWARD;
	ssize_t size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	usleep(3*micro);

	buffer[0] = STOP_M1;
	buffer[1] = 0;
	buffer[2] = 0;
	size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	usleep(3*micro);

	buffer[0] = STOP_M2;
	buffer[1] = 0;
	buffer[2] = 0;
	size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	usleep(3*micro);
	
	buffer[0] = SET_POWER_M1;
	buffer[1] = HALF_THROTTLE;
	buffer[2] = FORWARD;
	size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	usleep(3*micro);

	buffer[0] = BRAKE_M2;
	buffer[1] = 0;
	buffer[2] = 0;
	size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	usleep(3*micro);

	buffer[0] = REVERSE_POWER_M1;
	buffer[1] = 0;
	buffer[2] = 0;
	size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	usleep(3*micro);

	buffer[0] = STOP_ALL;
	buffer[1] = 0;
	buffer[2] = 0;
	size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size)
		cout << "An error occured during data sending..." << endl;

	// strcpy(&buffer, {SET_POWER_ALL, FULL_THROTTLE, BACKWARD});
	// size = sizeof(buffer);

	// size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	// if (size_sent != size)
	// {
	// 	cout << "An error occured during data sending..." << endl;
	// }

	// /* From i2c 0x0 address read 256 bytes data to buffer */
	// if ((i2c_read(&device, 0x0, buffer, size)) != size)
	// {
	// 	cout << "An error occured during reading..." << endl;
	// }

	i2c_close(bus);

	return 0;
}
