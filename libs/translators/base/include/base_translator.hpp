#pragma once

#include <string>
#include <vector>

namespace translators
{
    class BaseTranslator
    {
    protected:
        std::vector<std::vector<std::string>> m_text;
        std::string m_exe_name;
        //std::vector<std::vector<std::string>> m_code;
        //std::vector<std::vector<std::string>> m_data;

    public:
        BaseTranslator(){};

        void add_line(std::vector<std::string>& line);
        void print();

        virtual void write_to_binary(){};
    };

    // Pipeline:
    // File validator -> Formatter -> (classes starts to work here) -> Structure validator

    // Von Neumann arch: Programm contains only in memory (RAM) -> single bin file
    // Harvard arch: Programm contains in PROM (instructions), RAM (heap data) and stack (stack data) -> multiple bin files
}