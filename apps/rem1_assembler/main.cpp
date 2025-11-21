#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <validators.hpp>
#include <formatters.hpp>
#include <rem1_translator.hpp>

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

    const char* file_name = argv[1];
    
    // Loading content of asm source to memory
    std::ifstream asm_file;
    asm_file.open(file_name);

    std::vector<std::string> text;

    formatters::extract_lines_from_file(asm_file, text);
    asm_file.close();

    std::vector<std::string> tokens;

    // Adding lines to translator in convenient form
    rem1::Rem1Translator translator;
    for(const std::string& line : text)
    {
        formatters::tokenize_string(line, tokens);
        translator.add_line(tokens);

        tokens.clear();
    }

    // Convert assembly source to machine code
    rem1::Rem1CodeSegment code_seg("code");
    rem1::Rem1DataSegment data_seg("data");

    translator.add_segment(code_seg);
    translator.add_segment(data_seg);

    translator.load_segment(code_seg, "section", ".code");
    code_seg.prepare_text();
    code_seg.convert_to_binary();

    translator.load_segment(data_seg, "section", ".data");
    data_seg.convert_to_binary();

    translator.append_to_binary_from_segment(data_seg);
    translator.append_to_binary_from_segment(code_seg);

    // Write result to binary file
    std::filesystem::path bin_file_path = file_name;
    bin_file_path.replace_extension("bin");

    std::ofstream bin_file;
    bin_file.open(bin_file_path, std::ios::binary);

    translator.write_to_binary(bin_file);

    bin_file.close();

    return 0;
}