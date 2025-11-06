#include "validators.hpp"

#include <iostream>
#include <filesystem>

namespace validators
{
    int validate_asm_file(int argc, char** argv)
    {
        if(argc <= 1) // No arguments passed
        {
            std::cout << "Error: no input files!\n";
            return 3;
        }
        else if(argc > 2) // Too many arguments
        {
            std::cout << "Error: passed too many arguments! Please, pass only an assembly code file!\n";
            return 4;
        }
        std::filesystem::path asm_file_path = argv[1];
        if(asm_file_path.extension()!=".asm")
        {
            std::cout << "Error: wrong file format!\n";
            return 5;
        }
        return 0;
    }
}