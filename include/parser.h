//
// Created by horia on 04/05/23.
//

#ifndef EVAL_PARSER_H
#define EVAL_PARSER_H

#include "tokens.h"
#include "lexer.h"
#include "ASTNodes.h"

#include <vector>
#include <memory>
#include <iostream>
#include <map>

class Parser {
public:
    explicit Parser(std::string_view input);

    auto parse() -> std::unique_ptr<ExprAST>;

private:

    std::map<char, int> m_binop_precedence {
            {'+', 1},
            {'-', 1},
            {'*', 2},
            {'/', 2}
    };

    auto advance() -> void;
    [[nodiscard]] auto match(TokenType type) const -> bool;
    auto stmts() -> std::unique_ptr<ExprAST>;
    auto expr() -> std::unique_ptr<ExprAST>;
    auto term() -> std::unique_ptr<ExprAST>;
    auto factor() -> std::unique_ptr<ExprAST>;
    static auto log_error(std::string_view error) -> std::unique_ptr<ExprAST>;
    auto parse_paren_expr() -> std::unique_ptr<ExprAST>;


private:
    Lexer m_lexer;
    Token m_current_token {};

};

#endif //EVAL_PARSER_H
