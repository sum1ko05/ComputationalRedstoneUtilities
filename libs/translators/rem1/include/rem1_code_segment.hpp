#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <base_segment.hpp>

namespace rem1
{
    class Rem1CodeSegment: public translators::BaseSegment
    {
        
    };
}
/*
namespace translators
{
    class BaseSegment
    {
    protected:
        std::vector<std::vector<std::string>> m_text;
        std::vector<uint8_t> m_binary;

    public:
        BaseSegment(){};

        std::vector<uint8_t> get_binary() const {return m_binary;};

        virtual void prepare_text(){};
        virtual void convert_to_binary(){};

        void add_line(const std::vector<std::string>& line);
        void print() const;
    };
}
*/