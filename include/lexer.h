//
// Created by horia on 04/05/23.
//

#ifndef EVAL_LEXER_H
#define EVAL_LEXER_H

#include "tokens.h"
#include <iostream>
#include <string>
#include <string_view>

class Lexer {
public:
    explicit Lexer(std::string_view input) : m_input {input}, m_pos {0}, m_line {0} {

    }

    auto get_next_token() -> Token;

    [[nodiscard]] auto get_line() const -> int;

    [[nodiscard]] auto get_pos() const -> std::size_t;

private:
    std::string_view m_input {};
    std::size_t m_pos {};
    int m_line {};

    static auto parse_number(std::string_view number_str) -> double;


};

#endif //EVAL_LEXER_H
