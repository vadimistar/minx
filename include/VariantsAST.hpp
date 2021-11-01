//
// Created by vadi on 10/31/21.
//

#ifndef MINX_VARIANTSAST_HPP
#define MINX_VARIANTSAST_HPP

#include <variant>

namespace minx {

struct IntegerLiteralAST;
struct RefExprAST;
struct ReturnStmtAST;
struct VarDeclAST;

using ExprAST = std::variant<IntegerLiteralAST, RefExprAST>;
using StatementAST = std::variant<std::monostate, ReturnStmtAST, VarDeclAST>;

}

#endif // MINX_VARIANTSAST_HPP
