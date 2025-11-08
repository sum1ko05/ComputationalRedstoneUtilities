#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <validators.hpp>
#include <formatters.hpp>

int main(int argc, char** argv)
{
    // Validation
    int validator_return_code = validators::validate_asm_file(argc, argv);
    if(validator_return_code != 0) return validator_return_code;

    std::ifstream asm_file;
    asm_file.open(argv[1]);

    std::vector<std::string> text;

    formatters::extract_lines_from_file(asm_file, text);
    std::vector<std::string> tokens;
    for(const std::string& line : text)
    {
        //std::cout << line << std::endl;
        formatters::tokenize_string(line, tokens);
        for(const std::string& token : tokens)
        {
            std::cout << "[" << token << "] ";
        }
        std::cout << std::endl;
        tokens.clear();
    }

    asm_file.close();
}