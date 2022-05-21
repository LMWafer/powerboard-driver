#include "i2c/i2c.h"

class Board
{
    private:
        I2CDevice *device;
        unsigned char buffer[3];
        ssize_t size;
        int sendBuffer();
        short int correctValue(short int value);
    
    public:
        Board(unsigned int address, const char *bus_name);

        int enableBoard();
        int disableBoard();

        int setPowerAll(short int power);
        int setPowerM1(short int power);
        int setPowerM2(short int power);

        int stopAll();
        int stopM1();
        int stopM2();

        int brakeAll();
        int brakeM1();
        int brakeM2();

        int reversePowerAll();
        int reversePowerM1();
        int reversePowerM2();
};