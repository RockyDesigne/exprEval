//
// Created by horia on 04/05/23.
//
#include "../include/parser.h"

auto Parser::stmts() -> std::unique_ptr<ExprAST> {

    auto lhs {expr()};
    if (!lhs) {
        return nullptr;
    }
    if (match(TokenType::SEMI)) {
        advance();
        auto rhs {stmts()};
        if (!rhs) {
            return nullptr;
        }
        auto stmts_node {std::make_unique<BinaryExprAST>(';', std::move(lhs), std::move(rhs))};
        return stmts_node;
    }
    return lhs;

}

auto Parser::expr() -> std::unique_ptr<ExprAST> {
    auto lhs {term()};
    while (match(TokenType::PLUS) || match(TokenType::MINUS)) {
        char op {m_current_token.lexeme[0]};
        advance();
        auto rhs {term()};
        if (!rhs) {
            return nullptr;
        }
        lhs = std::make_unique<BinaryExprAST>(op, std::move(lhs), std::move(rhs));
    }
    return lhs;
}

auto Parser::factor() -> std::unique_ptr<ExprAST> {
    if (match(TokenType::NUM)) {
        auto node {std::make_unique<NumberExprAST>(m_current_token.val)};
        advance();
        return node;
    } else if (match(TokenType::LPAREN)) {
        return parse_paren_expr();
    }

    return nullptr;
}

auto Parser::term() -> std::unique_ptr<ExprAST> {
    auto lhs {factor()};
    while (match(TokenType::STAR) || match(TokenType::SLASH)) {
        auto op {m_current_token.lexeme[0]};
        advance();
        auto rhs {factor()};
        if (!rhs) {
            return nullptr;
        }
        lhs = std::make_unique<BinaryExprAST>(op, std::move(lhs), std::move(rhs));
    }
    return lhs;
}

auto Parser::match(TokenType type) const -> bool {
    return m_current_token.type == type;
}

auto Parser::advance() -> void {
    m_current_token = m_lexer.get_next_token();
}

Parser::Parser(std::string_view input) : m_lexer {input} {

    m_current_token = m_lexer.get_next_token();

}

auto Parser::log_error(std::string_view error) -> std::unique_ptr<ExprAST> {
    std::cerr << error << std::endl;
    return nullptr;
}

auto Parser::parse() -> std::unique_ptr<ExprAST> {
    return stmts();
}

auto Parser::parse_paren_expr() -> std::unique_ptr<ExprAST> {
    if (!match(TokenType::LPAREN))
        return log_error("Expected '(' on line " + std::to_string(m_current_token.line));

    advance();
    auto res {expr()};

    // Expect a closing parenthesis
    if (!match(TokenType::RPAREN))
        return log_error("Expected ')' on line " + std::to_string(m_current_token.line));

    advance();  

    return res;
}
