#include "formatters.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

namespace formatters
{
    /// @brief Returns a code line without comments and unnecessary whitespaces
    /// @param str Reference code line, from what comments and whitespaces should be removed
    /// @param whitespace String containing whitespaces to remove
    /// @param comment String containing comment starters to remove
    /// @return `str`, but without comments and unnecessary whitespaces. `str` will not be changed
    std::string trim_code_line(const std::string& str,
                               const std::string& whitespace,
                               const std::string& comment)
    {
        // Removing comments
        const size_t commentBegin = str.find_first_of(comment);
        std::string decommentedStr;
        if (commentBegin != std::string::npos) decommentedStr = str.substr(0, commentBegin);
        else decommentedStr = str;

        // Removing whitespaces from the sides
        const size_t lineBegin = decommentedStr.find_first_not_of(whitespace);
        if (lineBegin == std::string::npos)
            return ""; // actually empty string

        const size_t lineEnd = decommentedStr.find_last_not_of(whitespace);
        const size_t lineRange = lineEnd - lineBegin + 1;

        return decommentedStr.substr(lineBegin, lineRange);
    }

    /// @brief Read lines from stream into a vector of strings and trim them
    /// @param in Input file stream
    /// @param lines Vector of lines to store into
    void extract_lines_from_file(std::ifstream& in, 
                                 std::vector<std::string>& lines)
    {
        std::string single_line;
    
        if(in.is_open())
        {
            while(std::getline(in, single_line))
            {
                single_line = formatters::trim_code_line(single_line);
                if(single_line != "")
                {
                    lines.push_back(single_line);
                }
            }
        }
    }

    /// @brief Break a string to vector of words
    /// @param str String to break to tokens
    /// @param tokens Vector of tokens to store into
    /// @param whitespace Whitespace char to remove from `str`
    void tokenize_string(const std::string& str,
                         std::vector<std::string>& tokens,
                         const char& whitespace)
    {
        std::stringstream stream(str);
        std::string single_token;
        while(std::getline(stream, single_token, whitespace))
        {
            tokens.push_back(single_token);
        }
    }
}