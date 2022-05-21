#include "i2c/i2c.h"

class Board
{
    private:
        I2CDevice device;
        unsigned char buffer[3];
        ssize_t size;
    
    public:
        Board::Board(unsigned int address, const char *bus_name="/dev/i2c-1");
};
int enableBoard();
int disableBoard();

int setPowerAll();
int setPowerM1();
int setPowerM2();

int stopAll();
int stopM1();
int stopM2();

int brakeAll();
int brakeM1();
int brakeM2();

int reversePowerAll();
int reversePowerM1();
int reversePowerM2();
