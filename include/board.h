#include "i2c/i2c.h"
#include <iostream>
#include <cstdint>

using namespace std;

class Board
{
    private:
        I2CDevice device;
        unsigned char buffer_4[4];
        unsigned char buffer_3[3];
        unsigned char buffer_2[2];
        ssize_t size_4;
        ssize_t size_3;
        ssize_t size_2;
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

        struct Bridge
        {
            Board *owner;
            
            bool enableMA();
            bool disableMA();
            bool isMAEnabled();

            bool enableMB();
            bool disableMB();
            bool isMBEnabled();

            uint8_t setSignalIN1(uint8_t setPoint);
            uint8_t setSignalIN2(uint8_t setPoint);
            uint8_t setSignalIN3(uint8_t setPoint);
            uint8_t setSignalIN4(uint8_t setPoint);

            uint8_t getSignalIN1();
            uint8_t getSignalIN2();
            uint8_t getSignalIN3();
            uint8_t getSignalIN4();
        };
        Bridge bridge;

        struct Buck
        {
            bool enableRegulator();
            bool disableRegulator();
            bool isRegulatorEnabled();

            bool enableInput();
            bool disableInput();
            bool isInputEnabled();

            bool enableOutput();
            bool disableOutput();
            bool isOutputEnabled();
        };
        Buck buck;
};
