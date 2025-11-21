#include "rem1_translator.hpp"

#include <iostream>
#include <fstream>

//#include <base_translator.hpp>
//#include <base_segment.hpp>

namespace rem1
{
    /// @brief Retrieve all bytes from segment object to translator
    /// @param seg Segment object to retrieve binary info from
    void Rem1Translator::append_to_binary_from_segment(const translators::BaseSegment& seg)
    {
        const std::vector<uint8_t> binary_to_append = seg.get_binary();
        for(size_t i=0; i < binary_to_append.size(); ++i)
        {
            if(i >= m_binary.size()) // Will not fit in current vector
            {
                m_binary.push_back(binary_to_append[i]);
            }
            else // Will not fit in current vector
            {
                m_binary[i] = binary_to_append[i];
            }
        }
    }

    void Rem1Translator::write_to_binary(std::ofstream& out)
    {
        //std::cout << "Binary output started!\n";
        for(const uint8_t& byte : m_binary)
        {
            //std::cout << static_cast<int>(byte) << " ";
            out << byte;
        }
    }
}