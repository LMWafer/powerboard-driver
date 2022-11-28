pybind11_add_module(pypowerboard board.cpp)

target_include_directories(pypowerboard INTERFACE 
    ${PROJECT_SOURCE_DIR}/thirdparty/pybind11/include
)

target_link_libraries(pypowerboard PRIVATE 
    powerboard-driver
)
