find_package(PythonLibs 3 REQUIRED)

# LIST(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/thirdparty/pybind11/tools)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty/pybind11/include)
# include(pybind11Tools)

pybind11_add_module(pypowerboard board.cpp)

target_include_directories(pypowerboard INTERFACE
    ${PROJECT_SOURCE_DIR}
    ${PYTHON_INCLUDE_DIRS}
)

target_link_libraries(pypowerboard PRIVATE jetson-i2c-powerboard)
