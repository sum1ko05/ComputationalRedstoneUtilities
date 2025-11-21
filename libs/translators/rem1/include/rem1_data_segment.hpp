#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <base_segment.hpp>

namespace rem1
{
    class Rem1DataSegment: public translators::BaseSegment
    {
    public:
        Rem1DataSegment(const std::string& name): BaseSegment(name){};

        void prepare_text() override;
        void convert_to_binary() override;
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

    private:
        std::string m_segment_name;

    public:
        BaseSegment(const std::string& name)
        {
            m_segment_name = name;
        };
        ~BaseSegment(){};

        std::vector<uint8_t> get_binary() const {return m_binary;};

        virtual void prepare_text(){};
        virtual void convert_to_binary(){};

        void add_line(const std::vector<std::string>& line);
        void print() const;
    };
}
*/