#pragma once

#include <string>
#include <vector>
#include <cstdint>

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
        std::string get_segment_name() const {return m_segment_name;};

        /// @brief Makes text of segment readable for translator
        /// @warning Method from base class does nothing. 
        ///          Implement it yourself in inherited classes
        virtual void prepare_text(){};
        /// @brief Generates vector of bytes, based on segment text, and stores it in `m_binary`
        /// @warning Method from base class does nothing. 
        ///          Implement it yourself in inherited classes
        virtual void convert_to_binary(){};

        void add_line(const std::vector<std::string>& line);
        void print() const;
    };
}