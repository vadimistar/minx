//
// Created by vadi on 10/30/21.
//

#ifndef MINX_VISITOR_HPP
#define MINX_VISITOR_HPP

#include <variant>

namespace minx {

struct IdentifierAST;
struct PrimitiveTypeAST;
struct PointerTypeAST;
using TypeAST = std::variant<PrimitiveTypeAST, PointerTypeAST>;
struct IntegerLiteralAST;
struct ReturnStmtAST;
struct VarDeclAST;
using StatementAST = std::variant<std::monostate, ReturnStmtAST, VarDeclAST>;
struct CompoundStmtAST;
struct FuncDeclAST;
struct VarDeclAST;
struct TranslationUnitAST;

struct Visitor {
  virtual void visitIdentifier(IdentifierAST &) noexcept = 0;
  virtual void visitType(TypeAST &) noexcept = 0;
  virtual void visitPrimitiveType(PrimitiveTypeAST &) noexcept = 0;
  virtual void visitPointerType(PointerTypeAST &) noexcept = 0;
  virtual void visitIntegerLiteral(IntegerLiteralAST &) noexcept = 0;
  virtual void visitStatement(StatementAST &) noexcept = 0;
  virtual void visitReturnStmt(ReturnStmtAST &) noexcept = 0;
  virtual void visitCompoundStmt(CompoundStmtAST &) noexcept = 0;
  virtual void visitFuncDecl(FuncDeclAST &) noexcept = 0;
  virtual void visitVarDecl(VarDeclAST &) noexcept = 0;
  virtual void visitTranslationUnit(TranslationUnitAST &) noexcept = 0;
};

}

#endif // MINX_VISITOR_HPP
