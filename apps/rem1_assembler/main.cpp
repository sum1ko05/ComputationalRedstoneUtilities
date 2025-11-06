#include <iostream>
#include <fstream>
#include <filesystem>

#include <validators.hpp>

int main(int argc, char** argv)
{
    // Validation
    int validator_return_code = validators::validate_asm_file(argc, argv);
    if(validator_return_code != 0) return validator_return_code;

    std::ifstream asm_file;
    asm_file.open(argv[1]);

    asm_file.close();
}