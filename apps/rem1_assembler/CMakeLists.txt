set(EXECUTABLE_NAME rem1_asm)

add_executable(${EXECUTABLE_NAME} main.cpp)

target_link_libraries(${EXECUTABLE_NAME}
    validators
    formatters
    translators_base
    translators_rem1
)