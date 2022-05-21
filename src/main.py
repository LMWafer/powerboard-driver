import ctypes
import pylibi2c

slave_adress = 0x70


bus = "/dev/i2c-1"
device = 0x70
page_bytes = 16
iaddr_bytes = 1
delay = 10
i2c = pylibi2c.I2CDevice(bus=bus, addr=device, page_bytes=page_bytes, iaddr_bytes=iaddr_bytes, delay=delay)

iaddr = 0x0

# Set delay
i2c.delay = 10

# Set page_bytes
i2c.page_bytes = 16

# Set flags
i2c.flags = pylibi2c.I2C_M_IGNORE_NAK

# Python3
set_power_all = bytes([0x02])
full_throttle = bytes([0xFF])
forward = bytes([0x00])

# Write data to i2c, buf must be read-only type
# print("Sending", set_power_all, full_throttle, forward)
# size = i2c.write(iaddr, set_power_all)
# print(size)
# size = i2c.write(iaddr, full_throttle)
# print(size)
# size = i2c.write(iaddr, forward)
# print(size)

data = i2c.read(iaddr, 7)
print(data)

i2c.write(iaddr, set_power_all)
i2c.write(iaddr, full_throttle)
i2c.write(iaddr, forward)
data = i2c.read(iaddr, 7)
print(data)

i2c.close()
