#include "rem1_data_segment.hpp"

#include <iostream>
#include <map>
#include <cstdint>

namespace rem1
{
    /// @brief Makes text of segment readable for translator
    ///
    /// (no preprocessing is needed for REM-1 assembly sources)
    void Rem1DataSegment::prepare_text()
    {

    }

    /// @brief Generates vector of bytes, based on segment text, and stores it in `m_binary`
    void Rem1DataSegment::convert_to_binary()
    {
        std::map<uint16_t, uint8_t> preinit_data_map;

        uint16_t address;
        uint8_t value;
        uint16_t max_address = 0;

        // Extract initial data
        for(const std::vector<std::string>& line : m_text)
        {
            if(line[0] == "real")
            {
                if(line.size() == 4)
                {
                    address = static_cast<uint16_t>(std::stoi(line[1], nullptr, 0) & 0xFFFF);
                    value = static_cast<uint8_t>(std::stoi(line[3], nullptr, 0) & 0xFF);
                    preinit_data_map.insert({address, value});
                    max_address = std::max(max_address, address);
                }
                else throw std::logic_error("Data initialisation line should have 2 arguments and the token in the middle");
            }
            else throw std::logic_error("Only real addresses are implemented now");
        }

        // Put all of this data to m_binary
        m_binary = std::vector<uint8_t>(max_address + 1, 0);
        for(const std::pair<uint16_t, uint8_t>& cell : preinit_data_map)
        {
            m_binary[cell.first] = cell.second;
        }
    }
}