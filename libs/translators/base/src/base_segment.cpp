#include "base_segment.hpp"

#include <iostream>

namespace translators
{   
    /// @brief Add new line to the text of the segment
    /// @param line String to add
    void BaseSegment::add_line(const std::vector<std::string>& line)
    {
        m_text.push_back(line);
    }

    /// @brief Print the whole text of the segment with token highlighting
    void BaseSegment::print() const
    {
        for(const std::vector<std::string>& line : m_text)
        {
            for(const std::string& token : line)
            {
                std::cout << "[" << token << "] ";
            }
            std::cout << std::endl;
        }
    }
}