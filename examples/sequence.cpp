#include "board.h"
#include<unistd.h>

int main(){
    unsigned int microsecond = 1000000;

    Board board1(112, "/dev/i2c-1");
    board1.enable();
    usleep(3 * microsecond);
    board1.setPowerAll(254);
    usleep(3 * microsecond);
    board1.stopM2();
    usleep(3 * microsecond);
    board1.stopM1();
    usleep(3 * microsecond);
    board1.brakeAll();
    usleep(3 * microsecond);
    board1.reversePowerM1();
    usleep(3 * microsecond);
    board1.stopAll();
    
    return 0;
}
