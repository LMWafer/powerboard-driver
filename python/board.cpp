#include "board.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;

PYBIND11_MODULE(pypowerboard, module_handle) {
    module_handle.doc() = "A python binding for jetson-i2c-powerboard driver.";
    py::class_<Board> board(module_handle, "Board");
    
    board.def(py::init<const int, const string &>());

    board.def("enable", &Board::enable, "Enable board components. This allows power to be converted, PWM to be amplified, signals to pass from/to interface connectors etc.");
    board.def("disable", &Board::disable, "Disable board components. Everything is shudown except board microcontroller.");

    board.def("set_power_all", &Board::setPowerAll, "Change power setpoint of both motors.");
    board.def("set_power_m1", &Board::setPowerM1, "Change power setpoint of motor 1.");
    board.def("set_power_m2", &Board::setPowerM2, "Change power setpoint of motor 2.");

    board.def("stop_all", &Board::stopAll, "Put power setpoint of both motors to 0. 'Stop mode' or 'Idle mode' or 'Free wheel mode' : simply remove power from motor pins. Rotation inertia will generate the so called back EMF, that is a current flowing back from motor pins.");
    board.def("stop_m1", &Board::stopM1, "Put power setpoint of motor 1 to 0. 'Stop mode' or 'Idle mode' or 'Free wheel mode' : simply remove power from motor pins. Rotation inertia will generate the so called back EMF, that is a current flowing back from motor pins.");
    board.def("stop_m2", &Board::stopM2, "Put power setpoint of motor 2 to 0. 'Stop mode' or 'Idle mode' or 'Free wheel mode' : simply remove power from motor pins. Rotation inertia will generate the so called back EMF, that is a current flowing back from motor pins.");

    board.def("brake_all", &Board::brakeAll, "Set brake mode for both motors. 'Brake mode' or 'Coast mode' : connect motor pins together. Back EMF will be redirected at motor to use it as magnetic brake.");
    board.def("brake_m1", &Board::brakeM1, "Set brake mode for motor 1. 'Brake mode' or 'Coast mode' : connect motor pins together. Back EMF will be redirected at motor to use it as magnetic brake.");
    board.def("brake_m2", &Board::brakeM2, "Set brake mode for motor 2. 'Brake mode' or 'Coast mode' : connect motor pins together. Back EMF will be redirected at motor to use it as magnetic brake.");

    board.def("reverse_power_all", &Board::reversePowerAll, "Reverse power setpoint of both motors.");
    board.def("reverse_power_m1", &Board::reversePowerM1, "Reverse power setpoint of motor 1.");
    board.def("reverse_power_m2", &Board::reversePowerM2, "Reverse power setpoint of motor 2.");
}