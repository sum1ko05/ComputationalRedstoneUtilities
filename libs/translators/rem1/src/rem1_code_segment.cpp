#include "rem1_code_segment.hpp"

#include <iostream>
#include <vector>
#include <map>
#include <cstdint>
#include <regex>

namespace rem1
{
    /// @brief Converts labels to actual numbers behind them
    void Rem1CodeSegment::preprocess_labels()
    {
        std::map<std::string, size_t> label_map;

        // First find the labels
        for(size_t i=0; i < m_text.size(); ++i)
        {
            // More than 2 tokens in line => no point in checking more - not a jmp label
            if(m_text[i].size() == 1)
            {
                // Double-check to not get another out of range error 
                // (anyway it's impossible to get an empty token)
                if(m_text[i][0].size() > 0)
                {
                    // Check for token start (first character in i+1'th line in first word)
                    if(m_text[i][0][0] == '.')
                    {
                        label_map.insert({m_text[i][0], i});
                    }
                }
            }
        }

        // Then delete labels and replace it with actual addresses
        for(std::vector<std::string>& line : m_text)
        {
            // More than 2 tokens in line => no point in checking more - not a jmp label
            if(line.size() == 1)
            {
                // Double-check to not get another out of range error 
                // (anyway it's impossible to get an empty token)
                if(line[0].size() > 0)
                {
                    // Check for token start (first character in i+1'th line in first word)
                    if(line[0][0] == '.')
                    {
                        line[0] = "nop";
                    }
                }
            }
            else
            {
                for(std::string& token : line)
                {
                    // Double-check to not get another out of range error 
                    // (anyway it's impossible to get an empty token)
                    if(token.size() > 0)
                    {
                        // Check for token start (first character in i+1'th line in first word)
                        if(token[0] == '.')
                        {
                            // If label isn't in label map => find() will throw an end()
                            if(label_map.find(token) != label_map.end())
                            {
                                    token = std::to_string(label_map.find(token)->second);
                            }
                            else throw std::logic_error("Label wasn't found in label map! Label finding or checking failure detected!");
                        }
                    }
                }
            }
        }
    }
    
    /// @brief Makes text of segment readable for translator
    ///
    /// It includes translating labels to numbers
    void Rem1CodeSegment::prepare_text()
    {
        preprocess_labels();
    }

    /// @brief Generates vector of bytes, based on segment text, and stores it in `m_binary`
    void Rem1CodeSegment::convert_to_binary()
    {
        uint16_t instruction = 0x0000;
        uint8_t byte_to_push = 0x00;

        std::string opcode;

        std::regex register_regex("(r)([0-9]|1[0-6])");

        for(const std::vector<std::string>& line : m_text)
        {
            // Check the first token for an opcode
            instruction = 0x0000;
            opcode = line[0];
            // Yanderedev moment:
            if(opcode == "nop")
            {
                instruction = 0x0000;
            }
            else if(opcode == "hlt")
            {
                instruction = 0x1000;
            }
            else if(opcode == "add")
            {
                instruction = 0x2000;
                if(line.size() != 4) throw std::logic_error("Syntax error! ADD instruction should have 3 operands!");

                uint8_t operand;

                for(int op = 1; op <= 3; ++op)
                {
                    if(std::regex_match(line[op], register_regex))
                    {
                        operand = static_cast<uint8_t>(std::stoi(line[op].substr(1)) & 0xF);
                    }
                    else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                    // Append operand to instruction
                    instruction |= (static_cast<uint16_t>(operand) << ((3 - op) * 4));
                }
            }
            else if(opcode == "sub")
            {
                instruction = 0x3000;
                if(line.size() != 4) throw std::logic_error("Syntax error! SUB instruction should have 3 operands!");

                uint8_t operand;

                for(int op = 1; op <= 3; ++op)
                {
                    if(std::regex_match(line[op], register_regex))
                    {
                        operand = static_cast<uint8_t>(std::stoi(line[op].substr(1)) & 0xF);
                    }
                    else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                    // Append operand to instruction
                    instruction |= (static_cast<uint16_t>(operand) << ((3 - op) * 4));
                }
            }
            else if(opcode == "nor")
            {
                instruction = 0x4000;
                if(line.size() != 4) throw std::logic_error("Syntax error! NOR instruction should have 3 operands!");

                uint8_t operand;

                for(int op = 1; op <= 3; ++op)
                {
                    if(std::regex_match(line[op], register_regex))
                    {
                        operand = static_cast<uint8_t>(std::stoi(line[op].substr(1)) & 0xF);
                    }
                    else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                    // Append operand to instruction
                    instruction |= (static_cast<uint16_t>(operand) << ((3 - op) * 4));
                }
            }
            else if(opcode == "and")
            {
                instruction = 0x5000;
                if(line.size() != 4) throw std::logic_error("Syntax error! AND instruction should have 3 operands!");

                uint8_t operand;

                for(int op = 1; op <= 3; ++op)
                {
                    if(std::regex_match(line[op], register_regex))
                    {
                        operand = static_cast<uint8_t>(std::stoi(line[op].substr(1)) & 0xF);
                    }
                    else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                    // Append operand to instruction
                    instruction |= (static_cast<uint16_t>(operand) << ((3 - op) * 4));
                }
            }
            else if(opcode == "xor")
            {
                instruction = 0x6000;
                if(line.size() != 4) throw std::logic_error("Syntax error! XOR instruction should have 3 operands!");

                uint8_t operand;

                for(int op = 1; op <= 3; ++op)
                {
                    if(std::regex_match(line[op], register_regex))
                    {
                        operand = static_cast<uint8_t>(std::stoi(line[op].substr(1)) & 0xF);
                    }
                    else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                    // Append operand to instruction
                    instruction |= (static_cast<uint16_t>(operand) << ((3 - op) * 4));
                }
            }
            else if(opcode == "rsh")
            {
                instruction = 0x7000;
                if(line.size() != 3) throw std::logic_error("Syntax error! RSH instruction should have 2 operands!");

                uint8_t operand;
                for(int op = 1; op <= 2; ++op)
                {
                    if(std::regex_match(line[op], register_regex))
                    {
                        operand = static_cast<uint8_t>(std::stoi(line[op].substr(1)) & 0xF);
                    }
                    else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                    // Append operand to instruction
                    instruction |= (static_cast<uint16_t>(operand) << ((2 - op) * 8));
                }
            }
            else if(opcode == "set")
            {
                instruction = 0x8000;
                if(line.size() != 3) throw std::logic_error("Syntax error! SET instruction should have 2 operands!");

                uint8_t operand;
                // Standard register extraction procedure
                if(std::regex_match(line[1], register_regex))
                {
                    operand = static_cast<uint8_t>(std::stoi(line[1].substr(1)) & 0xF);
                    instruction |= (static_cast<uint16_t>(operand) << 8);
                }
                else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                // Extracting 8 bit number
                try
                {
                    operand = static_cast<uint8_t>(std::stoi(line[2]) & 0xFF);
                    instruction |= static_cast<uint16_t>(operand);
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
            }
            else if(opcode == "adi")
            {
                instruction = 0x9000;
                if(line.size() != 3) throw std::logic_error("Syntax error! ADI instruction should have 2 operands!");

                uint8_t operand;
                // Standard register extraction procedure
                if(std::regex_match(line[1], register_regex))
                {
                    operand = static_cast<uint8_t>(std::stoi(line[1].substr(1)) & 0xF);
                    instruction |= (static_cast<uint16_t>(operand) << 8);
                }
                else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                // Extracting 8 bit number
                try
                {
                    operand = static_cast<uint8_t>(std::stoi(line[2]) & 0xFF);
                    instruction |= static_cast<uint16_t>(operand);
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
            }
            else if(opcode == "jmp")
            {
                instruction = 0xA000;
                if(line.size() != 2) throw std::logic_error("Syntax error! JMP instruction should have 1 operand!");

                uint16_t operand;
                // Extracting 10 bit address
                try
                {
                    operand = static_cast<uint16_t>(std::stoi(line[1]) & 0x3FF);
                    instruction |= static_cast<uint16_t>(operand);
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
            }
            else if(opcode == "brh")
            {
                instruction = 0xB000;
                if(line.size() != 3) throw std::logic_error("Syntax error! BRH instruction should have 2 operands!");

                uint16_t operand;
                // Extracting 2 bit condition
                try
                {
                    operand = static_cast<uint16_t>(std::stoi(line[1]) & 0x3);
                    instruction |= (static_cast<uint16_t>(operand) << 10);
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
                // Extracting 10 bit address
                try
                {
                    operand = static_cast<uint16_t>(std::stoi(line[2]) & 0x3FF);
                    instruction |= static_cast<uint16_t>(operand);
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
            }
            else if(opcode == "cal")
            {
                instruction = 0xC000;
                if(line.size() != 2) throw std::logic_error("Syntax error! Call instruction should have 1 operand!");

                uint16_t operand;
                // Extracting 10 bit address
                try
                {
                    operand = static_cast<uint16_t>(std::stoi(line[1]) & 0x3FF);
                    instruction |= static_cast<uint16_t>(operand);
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
            }
            else if(opcode == "ret")
            {
                instruction = 0xD000;
            }
            else if(opcode == "mld")
            {
                instruction = 0xE000;
                if(line.size() != 4) throw std::logic_error("Syntax error! MLD instruction should have 3 operands!");

                uint8_t operand;

                // Standard register extraction procedure
                if(std::regex_match(line[1], register_regex))
                {
                    operand = static_cast<uint8_t>(std::stoi(line[1].substr(1)) & 0xF);
                    instruction |= (static_cast<uint16_t>(operand) << 8);
                }
                else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                // Extracting 8 bit number
                try
                {
                    operand = static_cast<uint8_t>(std::stoi(line[2]) & 0xF);
                    instruction |= static_cast<uint16_t>(operand) << 4;
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
                // Standard register extraction procedure
                if(std::regex_match(line[3], register_regex))
                {
                    operand = static_cast<uint8_t>(std::stoi(line[3].substr(1)) & 0xF);
                    instruction |= (static_cast<uint16_t>(operand));
                }
                else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
            }
            else if(opcode == "mst")
            {
                instruction = 0xF000;
                if(line.size() != 4) throw std::logic_error("Syntax error! MST instruction should have 3 operands!");

                uint8_t operand;

                // Standard register extraction procedure
                if(std::regex_match(line[1], register_regex))
                {
                    operand = static_cast<uint8_t>(std::stoi(line[1].substr(1)) & 0xF);
                    instruction |= (static_cast<uint16_t>(operand) << 8);
                }
                else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
                // Extracting 8 bit number
                try
                {
                    operand = static_cast<uint8_t>(std::stoi(line[2]) & 0xF);
                    instruction |= static_cast<uint16_t>(operand) << 4;
                }
                catch(const std::exception& e)
                {
                    throw e;
                }
                // Standard register extraction procedure
                if(std::regex_match(line[3], register_regex))
                {
                    operand = static_cast<uint8_t>(std::stoi(line[3].substr(1)) & 0xF);
                    instruction |= (static_cast<uint16_t>(operand));
                }
                else throw std::logic_error("Syntax error! Operands didn't match to standard register format!");
            }
            else throw std::logic_error("Incorrect instruction mnemonic!");

            // Push this 16 bit instruction to binary in 2 bytes
            byte_to_push = static_cast<uint8_t>((instruction & 0xFF00) >> 8);
            m_binary.push_back(byte_to_push);
            byte_to_push = static_cast<uint8_t>(instruction & 0x00FF);
            m_binary.push_back(byte_to_push);
        }
    }
}