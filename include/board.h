#include "i2c/i2c.h"
#include <iostream>
#include <cstdint>

using namespace std;

class Board
{
private:
    I2CDevice device;
    int sendBuffer(unsigned char buffer[], ssize_t size);
    short int correctValue(short int value);

public:
    Board(const uint8_t address, const string &bus_name);

    bool arm();
    bool disarm();
    bool isArmed();

    int16_t *setSpeedAll(int16_t speed);
    int16_t setSpeedM1(int16_t speed);
    int16_t setSpeedM2(int16_t speed);

    int16_t getSpeedM1();
    int16_t getSpeedM2();

    int16_t *stopAll();
    int16_t stopM1();
    int16_t stopM2();

    int16_t *brakeAll();
    int16_t brakeM1();
    bool isM1Braked();
    int16_t brakeM2();
    bool isM2Braked();

    int16_t *reverseAll();
    int16_t reverseM1();
    int16_t reverseM2();
};
