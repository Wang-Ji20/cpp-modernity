set(HELLO_SOURCES main.cc)
add_executable(hello ${HELLO_SOURCES})

target_link_libraries(hello cppmodernity)
set_target_properties(hello PROPERTIES OUTPUT_NAME hello-world)
