#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

#include <validators.hpp>
#include <formatters.hpp>
//#include <base_translator.hpp>
#include <rem1_translator.hpp>
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
    
    std::ifstream asm_file;
    asm_file.open(file_name);

    std::vector<std::string> text;

    formatters::extract_lines_from_file(asm_file, text);
    asm_file.close();

    std::vector<std::string> tokens;

    rem1::Rem1Translator translator;

    for(const std::string& line : text)
    {
        formatters::tokenize_string(line, tokens);
        translator.add_line(tokens);

        tokens.clear();
    }

    translator.print();

    //translators::BaseSegment base_code_seg("code");
    rem1::Rem1CodeSegment base_code_seg("code");
    translators::BaseSegment base_data_seg("data");

    translator.add_segment(base_code_seg);
    translator.add_segment(base_data_seg);

    std::cout << "\n";

    translator.load_segment(base_code_seg, "section", ".code");
    base_code_seg.prepare_text();
    base_code_seg.convert_to_binary();
    base_code_seg.print();

    std::cout << "\n";

    translator.load_segment(base_data_seg, "section", ".data");
    base_data_seg.print();

    translator.append_to_binary_from_segment(base_code_seg);

    std::filesystem::path bin_file_path = argv[1];
    bin_file_path.replace_extension("bin");

    std::cout << bin_file_path << std::endl;

    std::ofstream bin_file;
    bin_file.open(bin_file_path, std::ios::binary);

    translator.write_to_binary(bin_file);

    bin_file.close();

    return 0;
}