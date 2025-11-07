#pragma once

#include <string>
#include <vector>

namespace formatters
{
    std::string trim_code_line(const std::string& str,
                               const std::string& whitespace = " \t",
                               const std::string& comment = ";");
    void extract_lines_from_file(std::ifstream& in, 
                                 std::vector<std::string>& lines);
}