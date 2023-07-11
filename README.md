# exprEval
An expression evaluator written in CPP using LLVM. I wrote a lexer and a recursive descent parser,
and then used LLVM to generate the IR and create an interpreter.

## Positive
- I set out to create an interpreter using LLVM that evaluates arithmetic expressions, and it works
- Reasonably fast
- Learned a lot

## Limitations
- It can only do basic arithemthic, such as addition, substraction, multiplication and division
- It doesn't recover well from all errors (still working on it)

## Installation
- You need Cmake and LLVM version >= 14
- CPP standard 17
