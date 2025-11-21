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