#include "base_translator.hpp"

#include <iostream>

namespace translators
{
    void BaseTranslator::add_line(std::vector<std::string>& line)
    {
        m_text.push_back(line);
    }

    void BaseTranslator::print()
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
}