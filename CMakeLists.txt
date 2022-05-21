cmake_minimum_required(VERSION 3.10.2)
project(i2c-nano)

include_directories(${PROJECT_NAME} thirdparty/libi2c/include)
add_executable(${PROJECT_NAME} src/i2c-nano.cpp)
link_libraries(${PROJECT_NAME} thirdparty/libi2c/libi2c.so)