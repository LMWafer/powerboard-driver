#include "board.h"
#include "pybind11/pybind11.h"

namespace py = pybind11;

PYBIND11_MODULE(pypowerboard, module_handle) {
    module_handle.doc() = "Python binding for jetson-I2C-powerboard C++ driver.";
    py::class_<Board> board(module_handle, "Board");
    
    board.def(py::init<const int, const string &>());

    board.def("enable_board", &Board::enableBoard);
    board.def("disable_board", &Board::disableBoard);

    board.def("set_power_all", &Board::setPowerAll);
    board.def("set_power_m1", &Board::setPowerM1);
    board.def("set_power_m2", &Board::setPowerM2);

    board.def("stop_all", &Board::stopAll);
    board.def("stop_m1", &Board::stopM1);
    board.def("stop_m2", &Board::stopM2);

    board.def("brake_all", &Board::brakeAll);
    board.def("brake_m1", &Board::brakeM1);
    board.def("brake_m2", &Board::brakeM2);

    board.def("reversePowerAll", &Board::reversePowerAll);
    board.def("reverse_power_m1", &Board::reversePowerM1);
    board.def("reverse_power_m2", &Board::reversePowerM2);
}