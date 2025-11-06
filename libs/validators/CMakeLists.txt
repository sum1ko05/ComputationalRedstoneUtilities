set(LIBRARY_NAME validators)

add_library(${LIBRARY_NAME} STATIC 
    src/validators.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC include)