cmake_minimum_required(VERSION 3.10.2)
project(jetson-i2c-powerboard)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

SET(INCLUDE_PATHS 
include/
thirdparty/libi2c/include
)

SET(LIBRARY_SOURCES
src/board.cpp
)

include_directories(${INCLUDE_PATHS})
# link_directories(thirdparty/libi2c/)

add_library(jetson-i2c-powerboard SHARED ${LIBRARY_SOURCES})
target_link_libraries(jetson-i2c-powerboard libi2c.so)

# target_include_directories()
install()