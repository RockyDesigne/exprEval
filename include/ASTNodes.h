//
// Created by horia on 05/05/23.
//

#ifndef EVAL_ASTNODES_H
#define EVAL_ASTNODES_H

#include <string_view>
#include <memory>
#include "llvm/IR/Value.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Constants.h"

class CodeGen;

class ExprAST {
public:
    virtual ~ExprAST() = default;
    virtual llvm::Value* codegen(CodeGen& codegen) = 0;
};

class NumberExprAST : public ExprAST {
    double m_val;
public:
    explicit NumberExprAST(double val) : m_val(val) {};
    llvm::Value* codegen(CodeGen& codegen) override;
};

class BinaryExprAST : public ExprAST {
    char m_op;
    std::unique_ptr<ExprAST> m_lhs, m_rhs;
public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> lhs, std::unique_ptr<ExprAST> rhs)
            : m_op(op), m_lhs(std::move(lhs)), m_rhs(std::move(rhs)) {};
    llvm::Value* codegen(CodeGen& codegen) override;
};

class CodeGen {
public:
    CodeGen()
            : m_context(), m_module("CodeGenModule", m_context), m_builder(m_context) {

    }

    auto get_context() -> llvm::LLVMContext& {
        return m_context;
    }

    auto get_module() -> llvm::Module& {
        return m_module;
    }

    auto get_builder() -> llvm::IRBuilder<>& {
        return m_builder;
    }

    auto get_module_pointer() -> llvm::Module* {
        return &m_module;
    }

    auto generate_ir(std::unique_ptr<ExprAST> ast) -> void {
        llvm::FunctionType* mainFunctionType = llvm::FunctionType::get(llvm::Type::getDoubleTy(m_context), false);
        llvm::Function* mainFunction = llvm::Function::Create(mainFunctionType, llvm::Function::ExternalLinkage, "main", m_module);
        llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(m_context, "entry", mainFunction);
        m_builder.SetInsertPoint(entryBlock);
        llvm::Value* result = ast->codegen(*this);
        m_builder.CreateRet(result);
    }

    auto write_ir_to_file(std::string_view filename) -> void {

        std::error_code errorCode;
        llvm::raw_fd_ostream fileStream(filename.data(), errorCode);
        if (!errorCode) {
            m_module.print(fileStream, nullptr);
            fileStream.close();
        } else {
            llvm::errs() << "Could not open file: " << filename << "\n";
        }
    }
private:
    llvm::LLVMContext m_context;
    llvm::Module m_module;
    llvm::IRBuilder<> m_builder;
};

#endif //EVAL_ASTNODES_H
