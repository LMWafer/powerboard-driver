#include "i2c/i2c.h"
#include <string.h>
#include <iostream>
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

	device.bus = bus;		/* Bus 0 */
	device.addr = 0x70;		/* Slave address is 0x50, 7-bit */
	device.page_bytes = 3; /* Device are capable of 16 bytes per page */
	device.tenbit = 0;
	device.iaddr_bytes = 0;
	device.flags = 0;

	// unsigned char buffer[256];
	// ssize_t size = sizeof(buffer);
	// memset(buffer, 0, sizeof(buffer));

	unsigned char buffer[3] = {0x02, 0xFF, 0x01};
	ssize_t size = sizeof(buffer);

	ssize_t size_sent = i2c_ioctl_write(&device, 0, buffer, size);
	if (size_sent != size) {
		cout << "An error occured during data sending..." << endl;
	}

	// /* From i2c 0x0 address read 256 bytes data to buffer */
	// if ((i2c_read(&device, 0x0, buffer, size)) != size)
	// {
	// 	cout << "An error occured during reading..." << endl;
	// }

	i2c_close(bus);

	return 0;
}
