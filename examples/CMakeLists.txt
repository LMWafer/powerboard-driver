add_executable(sequence sequence.cpp)

target_include_directories(sequence INTERFACE 
    ../include
)

target_link_libraries(sequence 
    jetson-i2c-powerboard
)

set_target_properties(sequence PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
