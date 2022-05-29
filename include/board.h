#include "i2c/i2c.h"
#include <iostream>

using namespace std;

class Board
{
    private:
        I2CDevice device;
        unsigned char buffer_3[3];
        unsigned char buffer_1[1];
        ssize_t size_3;
        ssize_t size_1;
        int sendBuffer(unsigned char buffer[], ssize_t size);
        short int correctValue(short int value);
    
    public:
        Board(const unsigned int address, const string &bus_name);

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