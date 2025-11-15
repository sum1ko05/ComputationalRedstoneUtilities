#include "base_translator.hpp"

#include <iostream>
#include <fstream>

namespace translators
{
    /// @brief Test whether text contains no lines (i.e. is empty)
    /// @return Return whether text contains no lines (i.e. its size is 0)
    bool BaseTranslator::is_text_empty() const
    {
        return m_text.empty();
    }

    /// @brief Check whether text is intended for target machine
    /// @param target_keyword Common target machine keyword
    /// @param target_name Specific target machine name
    /// @return Return whether text is intended for target machine
    bool BaseTranslator::is_text_for_target_machine(const std::string& target_keyword,
                                                    const std::string& target_name) const
    {
        for(const std::vector<std::string>& line : m_text)
        {
            // First check only for keyword as 1st token in line + safeguard
            if(line.size() == 2 && line[0] == target_keyword)
            {
                // Check 2nd token if it's the target machine info
                // We're also assuming, that code is targeted only to one machine
                // Then there's no point of checking more lines
                if(line[1] == target_name) return true;
                else return false;
            }
        }
        // In case if we didn't find anything about target machine
        return false;
    }
    
    /// @brief Add segment on the back
    /// @param seg Segment to add
    void BaseTranslator::add_segment(const BaseSegment& seg)
    {
        m_segments.push_back(seg);
    }

    /// @brief Loads lines from segment in text to segment object
    /// @param seg Segment object to load lines into
    /// @param segment_keyword Common segment keyword
    /// @param segment_name Specific name of target segment
    void BaseTranslator::load_segment(BaseSegment& seg, 
                                      const std::string& segment_keyword,
                                      const std::string& segment_name)
    {
        if(is_text_empty()) return;

        bool is_inside_section = false;
        for(const std::vector<std::string>& line : m_text)
        {
            // Actions outside segment
            if(!is_inside_section)
            {
                // First check only for keyword as 1st token in line
                if(line[0] == segment_keyword)
                {
                    // Check 2nd token if it's the start of our target section
                    if(line[1] == segment_name) is_inside_section = true;
                }
            }
            else // Actions inside segment
            {
                // If first token is segment keyword => target section ended
                // Then there are no reason to parse more lines
                if(line[0] == segment_keyword) return;
                // Else just include this line into segment object
                seg.add_line(line);
            }
        }
    }

    /// @brief Retrieve all bytes from segment object to translator
    /// @param seg Segment object to retrieve binary info from
    void BaseTranslator::append_to_binary_from_segment(const BaseSegment& seg)
    {
        const std::vector<uint8_t> seg_binary = seg.get_binary();
        for(const uint8_t& byte : seg_binary)
        {
            m_binary.push_back(byte);
        }
    }
    
    /// @brief Add new line to the text of the program
    /// @param line String to add
    void BaseTranslator::add_line(const std::vector<std::string>& line)
    {
        m_text.push_back(line);
    }

    /// @brief Print the whole text of the programm with token highlighting
    void BaseTranslator::print() const
    {
        for(const std::vector<std::string>& line : m_text)
        {
        //std::cout << line << std::endl;
            for(const std::string& token : line)
            {
                std::cout << "[" << token << "] ";
            }
            std::cout << std::endl;
        }
    }

    void BaseTranslator::write_to_binary(std::ofstream& out)
    {
        // Placeholder output to test writting to binary file
        std::string placeholder = "Placeholder output, please change class for real one, oguzok.";
        out << placeholder;
        out << (uint8_t)6 << (uint8_t)7;
    }
}