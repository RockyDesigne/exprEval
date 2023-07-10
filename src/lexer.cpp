//
// Created by horia on 04/05/23.
//
#include "../include/lexer.h"

auto Lexer::get_next_token() -> Token {

    // Skip whitespace characters
    while (m_pos < m_input.size() && std::isspace(m_input[m_pos])) {
        if (m_input[m_pos] == '\n') {
            m_line++;
        }
        m_pos++;
    }

    if (m_pos >= m_input.size()) {
        return Token {TokenType::EOI, "", m_line};
    }

    while (m_pos < m_input.size()) {

        if (std::isdigit(m_input[m_pos])) {

            // NUM Token

            std::string_view lexeme {};
            auto len {m_pos};

            while (m_pos < m_input.size() && std::isdigit(m_input[m_pos])) {

                ++m_pos;
                lexeme = std::string_view {&m_input[len], m_pos - len};

            }

            double number {parse_number(lexeme)};

            return Token {TokenType::NUM, lexeme, m_line, number};

        }

        switch (m_input[m_pos]) {

            case '+':
                ++m_pos;
                return Token {TokenType::PLUS, "+", m_line};
            case '-':
                ++m_pos;
                return Token {TokenType::MINUS, "-", m_line};
            case '*':
                ++m_pos;
                return Token {TokenType::STAR, "*", m_line};
            case '/':
                ++m_pos;
                return Token {TokenType::SLASH, "/", m_line};
            case '(':
                ++m_pos;
                return Token {TokenType::LPAREN, "(", m_line};
            case ')':
                ++m_pos;
                return Token {TokenType::RPAREN, ")", m_line};
            case ';':
                ++m_pos;
                return Token {TokenType::SEMI, ";", m_line};
            default:
                std::cerr << "Unexpected character: " << m_input[m_pos] << std::endl;
                ++m_pos;
                break;
        }

    }

    return Token {TokenType::EOI, "", m_line};
}

auto Lexer::parse_number(std::string_view number_str) -> double {
    return std::strtod(number_str.data(), nullptr);
}

auto Lexer::get_pos() const -> std::size_t {
    return m_pos;
}

auto Lexer::get_line() const -> int {
    return m_line;
}
