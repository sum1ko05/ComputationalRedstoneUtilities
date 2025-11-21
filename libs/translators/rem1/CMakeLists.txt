set(LIBRARY_NAME translators_rem1)

add_library(${LIBRARY_NAME} STATIC 
    src/rem1_code_segment.cpp
    src/rem1_data_segment.cpp
    src/rem1_translator.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC include)

target_link_libraries(${LIBRARY_NAME}
    translators_base
)