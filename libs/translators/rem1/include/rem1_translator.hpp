#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <base_translator.hpp>
#include <base_segment.hpp>

#include "rem1_code_segment.hpp"
#include "rem1_data_segment.hpp"

namespace rem1
{
    class Rem1Translator: public translators::BaseTranslator
    {
    public:
        void append_to_binary_from_segment(const translators::BaseSegment& seg) override;
        void write_to_binary(std::ofstream& out) override;
    };
}