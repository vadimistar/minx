#ifndef MINX_TYPEVALIDATOR_HPP
#define MINX_TYPEVALIDATOR_HPP

#include "Visitor.hpp"
#include "Ast.hpp"

namespace minx
{
struct Scope;
    
struct ScopeCreator : Visitor {
  void visitIdentifier(IdentifierAST &) noexcept override {}
  void visitType(TypeAST &) noexcept override {}
  void visitIntegerLiteral(IntegerLiteralAST &) noexcept override {}
  void visitStatement(StatementAST &) noexcept override {}
  void visitReturnStmt(ReturnStmtAST &) noexcept override;
  void visitCompoundStmt(CompoundStmtAST &) noexcept override;
  void visitFuncDecl(FuncDeclAST &) noexcept override;
  void visitVarDecl(VarDeclAST &) noexcept override;
  void visitTranslationUnit(TranslationUnitAST &) noexcept override;
  void visitExpr(ExprAST &) noexcept override {}
  void visitRefExpr(RefExprAST &) noexcept override {}

  Scope *scope;
}; 

} // namespace minx


#endif//MINX_TYPEVALIDATOR_HPP