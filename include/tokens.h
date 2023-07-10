//
// Created by horia on 04/05/23.
//

#ifndef EVAL_TOKENS_H
#define EVAL_TOKENS_H

#include <string_view>

enum class TokenType {
    NUM, // [0-9]+
    PLUS, // +
    MINUS, // -
    STAR, // *
    SLASH, // /
    LPAREN, // (
    RPAREN, // )
    SEMI, // ;
    EOI // End of input
};

struct Token {

    TokenType type {};
    std::string_view lexeme {};
    int line {};
    double val {};

};

#endif //EVAL_TOKENS_H
