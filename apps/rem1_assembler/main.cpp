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
    try
    {
        validators::validate_asm_file(argc, argv);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 3;
    }
    
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

    std::filesystem::path bin_file_path = argv[1];
    bin_file_path.replace_extension("bin");

    std::cout << bin_file_path << std::endl;

    std::ofstream bin_file;
    bin_file.open(bin_file_path, std::ios::binary);

    translator.write_to_binary(bin_file);

    bin_file.close();

    return 0;
}