//
// Created by vadi on 10/21/21.
//

#ifndef MINX_AST_HPP
#define MINX_AST_HPP

#include "Type.hpp"

#include <variant>
#include <vector>
#include <string>
#include <optional>

namespace minx {

struct IdentifierAST {
  std::string name;
};

struct PrimitiveTypeAST; struct PointerTypeAST;

using TypeAST = std::variant<PrimitiveTypeAST, PointerTypeAST>;

struct PrimitiveTypeAST {
  PrimitiveType type;
};

struct PointerTypeAST {
  TypeAST *dst;
};

struct IntegerLiteralAST {
  std::string value;
};

struct ReturnStmt {
  std::optional<IntegerLiteralAST> value;
};

using StatementAST = std::variant<std::monostate, ReturnStmt>;

struct CompoundStmt {
  std::vector<StatementAST> statements;
};

struct FuncDeclAST {
  IdentifierAST id;
  TypeAST returnType;
  CompoundStmt body;
};

struct TranslationUnitAST {
  std::vector<FuncDeclAST> funcDecls;
};

} // namespace minx

#endif // MINX_AST_HPP
