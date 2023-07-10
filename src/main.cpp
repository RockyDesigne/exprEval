//
// Created by horia on 04/05/23.
//

#include "../include/parser.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/GenericValue.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ExecutionEngine/Interpreter.h"
#include <memory>

auto printResult(const llvm::GenericValue& res) -> void {
    llvm::outs() << res.DoubleVal << '\n';
}

auto main() -> int {
    llvm::InitializeNativeTarget();
    llvm::InitializeNativeTargetAsmPrinter();

    auto repl {true};

    while (repl) {

        std::string input{};
        std::cout << ">>> ";
        std::getline(std::cin, input);
        if (input == "exit") {
            repl = false;
            continue;
        }
        Parser parser{input};
        auto ast{parser.parse()};
        if (!ast) {
            std::cout << "Error parsing input\n";
            return 1;
        }

        CodeGen codegen{};
        codegen.generate_ir(std::move(ast));
        codegen.write_ir_to_file("output.ll");

        std::string error{};

        std::unique_ptr<llvm::Module> module{
                std::make_unique<llvm::Module>("CodeGenModule", codegen.get_context())
        };

        llvm::EngineBuilder builder{std::move(module)};
        builder.setErrorStr(&error);
        builder.setEngineKind(llvm::EngineKind::Interpreter);

        llvm::ExecutionEngine *engine{
                builder.create()
        };

        if (!engine) {
            llvm::errs() << "Error: " << error << '\n';
            return 1;
        }

        llvm::GenericValue res{
                engine->runFunction(codegen.get_module_pointer()->getFunction("main"), {})
        };

        printResult(res);
    }

    return 0;
}
