#ifndef MINX_TYPEVALIDATOR_HPP
#define MINX_TYPEVALIDATOR_HPP

#include "Visitor.hpp"

namespace minx
{

struct Scope;

struct ScopeCreator : Visitor {
  void visitIdentifier(IdentifierAST &) noexcept override {}
  void visitType(TypeAST &) noexcept override {}
  void visitIntegerLiteral(IntegerLiteralAST &) noexcept override {}
  void visitStatement(StatementAST &) noexcept override {}
  void visitReturnStmt(ReturnStmtAST &) noexcept override {}
  void visitCompoundStmt(CompoundStmtAST &) noexcept override;
  void visitCompoundStmtExit(CompoundStmtAST &) noexcept;
  void visitFuncDecl(FuncDeclAST &) noexcept override;
  void visitVarDecl(VarDeclAST &) noexcept override;
  void visitTranslationUnit(TranslationUnitAST &) noexcept override;
  void visitTranslationUnitExit(TranslationUnitAST &) noexcept;
  void visitExpr(ExprAST &) noexcept override {}
  void visitRefExpr(RefExprAST &) noexcept override {}

  Scope *scope{nullptr};
}; 

} // namespace minx


#endif//MINX_TYPEVALIDATOR_HPP