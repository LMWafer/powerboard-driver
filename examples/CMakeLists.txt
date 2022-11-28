add_executable(sequence sequence.cpp)

target_include_directories(sequence INTERFACE 
    ../include
)

target_link_libraries(sequence 
    powerboard-driver
)

set_target_properties(sequence PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
