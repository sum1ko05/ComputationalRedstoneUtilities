set(LIBRARY_NAME formatters)

add_library(${LIBRARY_NAME} STATIC 
    src/formatters.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC include)