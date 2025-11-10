set(LIBRARY_NAME translators_base)

add_library(${LIBRARY_NAME} STATIC 
    src/base_translator.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC include)