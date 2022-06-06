#include "board.h"
#include <unistd.h>
#include <iostream>

using namespace std;

int main(){
    useconds_t threeMic = 3000000;

    Board board(112, "/dev/i2c-1");
    cout << "Arming board" << endl;
    board.arm();
    usleep(threeMic);
    cout << "Setting all motors to full throttle" << endl;
    board.setSpeedAll(255);
    usleep(threeMic);
    cout << "Stopping motor 2" << endl;
    board.stopM2();
    usleep(threeMic);
    cout << "Stopping motor 1" << endl;
    board.stopM1();
    usleep(threeMic);
    cout << "Setting motor 1 to half throttle" << endl;
    board.setSpeedM1(-128);
    usleep(threeMic);
    cout << "Reversing M1 direction" << endl;
    board.reverseM1();
    usleep(threeMic);
    cout << "Stopping all motors" << endl;
    board.stopAll();
    cout << "Disarming board" << endl;
    board.disarm();
    usleep(threeMic);
    cout << "Activating relay" << endl;
    board.buck.enableInput();
    usleep(threeMic);
    cout << "Deactivating relay" << endl;
    board.disarm();
    
    return 0;
}
