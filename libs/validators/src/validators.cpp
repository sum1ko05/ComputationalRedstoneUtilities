#include "validators.hpp"

#include <iostream>
#include <filesystem>
#include <string>

namespace validators
{
    /// @brief Make sure that user didn't make mistakes in passing asm file
    /// @param argc argc from int main()
    /// @param argv argv from int main()
    /// @return Return code (0 in case of success)
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

    int validate_file_structure(const std::string& target_machine)
    {
        return -1;
    }
}