#include "../include/ScopeCreator.hpp"
#include "../include/Scope.hpp"

namespace minx {

void ScopeCreator::visitVarDecl(VarDeclAST &decl) noexcept {
  assert(scope != nullptr);
  scope->add(decl.id, false, decl.type);
}
  
void ScopeCreator::visitTranslationUnit(TranslationUnitAST &) noexcept {
  scope = std::unique_ptr<Scope>().get(); 
}

void ScopeCreator::visitFuncDecl(FuncDeclAST &decl) noexcept {
  assert(scope != nullptr); 
  scope->add(decl.id, true, decl.returnType); 
}

void ScopeCreator::visitCompoundStmt(CompoundStmtAST &) noexcept {
  auto prevScope { scope };
  scope = std::unique_ptr<Scope>(prevScope).get();
}

} // namespace minx