cmake_minimum_required(VERSION 3.10.2)
project(jetson-i2c-powerboard)

#- Use the module that provides GNU standard installation directories
include(GNUInstallDirs)

#-[] Set project specific options
#-> Library build options
option(BUILD_PYTHON "Build python3 bindings of the driver." ON)
option(BUILD_EXAMPLES "Build examples alongside the library." ON)
#-> Tell the linker where to look for an external library
link_directories(thirdparty/libi2c/)

#-[] Set project specific files paths
#-> Where to look for ".h" files with "#include"
SET(INCLUDE_PATHS 
    include/
    thirdparty/libi2c/include
)
#-> Where to pick library source files
SET(LIBRARY_SOURCE_FILES
    src/board.cpp
)
#-> Files used as library headers but future devs
SET(LIBRARY_HEADERS_FILES
    include/board.h
    include/commands.h
)
#-> Library compilation output path
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)

#-[] Build project's library
#-> Create a shared library (a .so file) with given source files
add_library(jetson-i2c-powerboard SHARED ${LIBRARY_SOURCE_FILES})
#-> Give library paths for external libraries' header files
target_include_directories(jetson-i2c-powerboard PUBLIC ${INCLUDE_PATHS})
#-> Indicate which files are library's headers
set_target_properties(jetson-i2c-powerboard PROPERTIES PUBLIC_HEADER "${LIBRARY_HEADERS_FILES}")
#-> Link external libraries used by this library
target_link_libraries(jetson-i2c-powerboard libi2c.so)

#-[] Generate project installation rules
install(TARGETS jetson-i2c-powerboard 
        LIBRARY
            DESTINATION ${CMAKE_INSTALL_LIBDIR}/jetson-i2c-powerboard
        PUBLIC_HEADER 
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/jetson-i2c-powerboard)

#-[] Library's python bindings
if (BUILD_PYTHON)
    message(STATUS "Building python3 bindings...")
    add_subdirectory(thirdparty/pybind11)
    add_subdirectory(python)
endif(BUILD_PYTHON)

#-[] Library's CXX examples
if (BUILD_EXAMPLES)
    message(STATUS "Building examples..")
    add_subdirectory(examples)
endif(BUILD_EXAMPLES)
