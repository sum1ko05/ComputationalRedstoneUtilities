set(LIBRARY_NAME translators)
#[[
add_library(${LIBRARY_NAME} STATIC 
    src/rem1_translator.cpp
)

target_include_directories(${LIBRARY_NAME} PUBLIC include)
]]
#    WIP