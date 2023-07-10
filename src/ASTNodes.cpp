//
// Created by HORIA on 02.07.2023.
//
#include "../include/ASTNodes.h"

#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"

auto NumberExprAST::codegen(CodeGen& codegen) -> llvm::Value* {
    return llvm::ConstantFP::get(codegen.get_context(), llvm::APFloat(m_val));
}

auto BinaryExprAST::codegen(CodeGen &codegen) -> llvm::Value* {
    llvm::Value* lhs = m_lhs->codegen(codegen);
    llvm::Value* rhs = m_rhs->codegen(codegen);
    if (!lhs || !rhs) {
        return nullptr;
    }
    switch (m_op) {
        case '+':
            return codegen.get_builder().CreateFAdd(lhs, rhs, "addtmp");
        case '-':
            return codegen.get_builder().CreateFSub(lhs, rhs, "subtmp");
        case '*':
            return codegen.get_builder().CreateFMul(lhs, rhs, "multmp");
        case '/':
            return codegen.get_builder().CreateFDiv(lhs, rhs, "divtmp");
        default:
            llvm::errs() << "Invalid binary operator: " << m_op << "\n";
            return nullptr;
    }
}
