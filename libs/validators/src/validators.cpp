#include "validators.hpp"

#include <iostream>
#include <filesystem>
#include <string>

namespace validators
{
    /// @brief Make sure that user didn't make mistakes in passing asm file
    /// @param argc argc from int main()
    /// @param argv argv from int main()
    void validate_asm_file(int argc, char** argv)
    {
        if(argc <= 1) // No arguments passed
        {
            throw std::invalid_argument("No input files was passed!");
        }
        else if(argc > 2) // Too many arguments
        {
            throw std::invalid_argument("Passed too many arguments!");
        }
        std::filesystem::path asm_file_path = argv[1];
        if(asm_file_path.extension()!=".asm")
        {
            throw std::invalid_argument("Wrong file format!");
        }
    }
}