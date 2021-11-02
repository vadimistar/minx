#include "../include/ScopeCreator.hpp"
#include "../include/Scope.hpp"
#include "../include/Ast.hpp"

namespace minx {

void ScopeCreator::visitVarDecl(VarDeclAST &decl) noexcept {
  assert(scope != nullptr);
  scope->add(decl.id, false, decl.type);
}
  
void ScopeCreator::visitTranslationUnit(TranslationUnitAST&) noexcept {
  scope = new Scope(); 
}

void ScopeCreator::visitTranslationUnitExit(TranslationUnitAST&) noexcept {
  delete scope;
}

void ScopeCreator::visitFuncDecl(FuncDeclAST &decl) noexcept {
  scope->add(decl.id, true, decl.returnType); 
}

void ScopeCreator::visitCompoundStmt(CompoundStmtAST &) noexcept {
  scope = new Scope(scope);
}

void ScopeCreator::visitCompoundStmtExit(CompoundStmtAST &) noexcept {
  auto* curr { scope };
  scope = scope->prev;
  delete curr;
}

}