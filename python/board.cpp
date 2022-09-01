#include "board.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;

PYBIND11_MODULE(pypowerboard, module_handle) {
    module_handle.doc() = "A python binding for powerboard driver.";

    py::class_<Board> board(module_handle, "Board");
    board.def(py::init<const uint8_t, const string &>());

    board.def("arm", &Board::arm, "Enable board components. \nWARNING ! A conductive path is created from battery to motors, making the board dangerous to touch. \nThis function allows power to be converted, PWM to be amplified, signals to pass from/to interface connectors etc.");
    board.def("disarm", &Board::disarm, "Disable board components. \nEverything is shut down except microcontroller.");

    board.def("set_speed_all", &Board::setSpeedAll, "Change speed setpoint of both motors.");
    board.def("set_speed_m1", &Board::setSpeedM1, "Change speed setpoint of motor 1.");
    board.def("set_speed_m2", &Board::setSpeedM2, "Change speed setpoint of motor 2.");

    board.def("stop_all", &Board::stopAll, "Put speed setpoint of both motors to 0. \n'Stop mode' or 'Idle mode' or 'Free wheel mode' : simply remove power from motor pins. \nRotation inertia will generate the so called back EMF, that is a current flowing back from motor pins.");
    board.def("stop_m1", &Board::stopM1, "Put speed setpoint of motor 1 to 0. \n'Stop mode' or 'Idle mode' or 'Free wheel mode' : simply remove power from motor pins. \nRotation inertia will generate the so called back EMF, that is a current flowing back from motor pins.");
    board.def("stop_m2", &Board::stopM2, "Put speed setpoint of motor 2 to 0. \n'Stop mode' or 'Idle mode' or 'Free wheel mode' : simply remove power from motor pins. \nRotation inertia will generate the so called back EMF, that is a current flowing back from motor pins.");

    board.def("brake_all", &Board::brakeAll, "Set brake mode for both motors. \n'Brake mode' or 'Coast mode' : connect motor pins together. \nBack EMF will be redirected at motor to use it as magnetic brake.");
    board.def("brake_m1", &Board::brakeM1, "Set brake mode for motor 1. \n'Brake mode' or 'Coast mode' : connect motor pins together. \nBack EMF will be redirected at motor to use it as magnetic brake.");
    board.def("brake_m2", &Board::brakeM2, "Set brake mode for motor 2. \n'Brake mode' or 'Coast mode' : connect motor pins together. \nBack EMF will be redirected at motor to use it as magnetic brake.");

    board.def("reverse_speed_all", &Board::reverseAll, "Reverse speed setpoint of both motors.");
    board.def("reverse_speed_m1", &Board::reverseM1, "Reverse speed setpoint of motor 1.");
    board.def("reverse_speed_m2", &Board::reverseM2, "Reverse speed setpoint of motor 2.");
}
