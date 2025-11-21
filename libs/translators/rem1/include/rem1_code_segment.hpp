#pragma once

#include <string>
#include <vector>
#include <cstdint>

#include <base_segment.hpp>

namespace rem1
{
    class Rem1CodeSegment: public translators::BaseSegment
    {
    private:
        void preprocess_labels();
        void preprocess_pseudo_instructions();

    public:
        Rem1CodeSegment(const std::string& name): BaseSegment(name){};

        void prepare_text() override;
        void convert_to_binary() override;
    };
}