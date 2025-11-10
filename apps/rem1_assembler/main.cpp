#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <validators.hpp>
#include <formatters.hpp>
#include <base_translator.hpp>

int main(int argc, char** argv)
{
    // Validation
    int validator_return_code = validators::validate_asm_file(argc, argv);
    if(validator_return_code != 0) return validator_return_code;

    std::ifstream asm_file;
    asm_file.open(argv[1]);

    std::vector<std::string> text;

    formatters::extract_lines_from_file(asm_file, text);
    asm_file.close();

    std::vector<std::string> tokens;

    translators::BaseTranslator translator;

    for(const std::string& line : text)
    {
        formatters::tokenize_string(line, tokens);
        translator.add_line(tokens);

        tokens.clear();
    }

    translator.print();
}