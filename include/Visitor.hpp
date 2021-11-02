//
// Created by vadi on 10/30/21.
//

#ifndef MINX_VISITOR_HPP
#define MINX_VISITOR_HPP

#include "VariantsAST.hpp"

namespace minx {

struct IdentifierAST;
struct TypeAST;
struct IntegerLiteralAST;
struct RefExprAST;
struct ReturnStmtAST;
struct VarDeclAST;
struct CompoundStmtAST;
struct FuncDeclAST;
struct VarDeclAST;
struct TranslationUnitAST;

struct Visitor {
  virtual void visitIdentifier(IdentifierAST &) noexcept = 0;
  virtual void visitType(TypeAST &) noexcept = 0;
  virtual void visitIntegerLiteral(IntegerLiteralAST &) noexcept = 0;
  virtual void visitStatement(StatementAST &) noexcept = 0;
  virtual void visitReturnStmt(ReturnStmtAST &) noexcept = 0;
  virtual void visitCompoundStmt(CompoundStmtAST &) noexcept = 0;
  virtual void visitFuncDecl(FuncDeclAST &) noexcept = 0;
  virtual void visitVarDecl(VarDeclAST &) noexcept = 0;
  virtual void visitTranslationUnit(TranslationUnitAST &) noexcept = 0;
  virtual void visitExpr(ExprAST &) noexcept = 0;
  virtual void visitRefExpr(RefExprAST &) noexcept = 0;

  virtual ~Visitor() = default;
};

}

#endif // MINX_VISITOR_HPP
