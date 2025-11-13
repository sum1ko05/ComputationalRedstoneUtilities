#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include "base_segment.hpp"

namespace translators
{
    class BaseTranslator
    {
    protected:
        std::vector<std::vector<std::string>> m_text;
        std::vector<uint8_t> m_binary;
        std::vector<BaseSegment> m_segments;
        
    private:
        

    public:
        BaseTranslator(){};

        bool is_text_empty() const;

        void add_segment(const BaseSegment& seg);
        void load_segment(BaseSegment& seg, const std::string& segment_keyword,
                                            const std::string& segment_name);
        void append_to_binary_from_segment(const BaseSegment& seg);

        void add_line(const std::vector<std::string>& line);
        void print() const;

        virtual void write_to_binary(std::ofstream& out){};
    };

    // Pipeline:
    // File validator -> Formatter -> (classes starts to work here) -> Structure validator

    // Von Neumann arch: Programm contains only in memory (RAM) -> single bin file
    // Harvard arch: Programm contains in PROM (instructions), RAM (data) -> multiple bin files
}