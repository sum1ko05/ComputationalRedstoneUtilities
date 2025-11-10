#pragma once

#include <string>

namespace validators
{
    int validate_asm_file(int argc, char** argv);
    int validate_file_structure(const std::string& target_machine);
}