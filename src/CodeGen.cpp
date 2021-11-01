//
// Created by vadi on 10/30/21.
//

#include "../include/CodeGen.hpp"
#include "../include/Ast.hpp"
#include "../include/Type.hpp"
#include "../include/Scope.hpp"

namespace minx {
CodeGen::CodeGen() noexcept {
  scope = std::make_unique<Scope>().get(); 
}

void CodeGen::visitFuncDecl(FuncDeclAST &funcDecl) noexcept {
  defineRetType = getLLVMType(funcDecl.returnType);
  emitDefineHeader(defineRetType, funcDecl.id.name);
  scope = std::make_unique<Scope>(scope).get();
}

void CodeGen::visitReturnStmt(ReturnStmtAST & stmt) noexcept {
  if (stmt.value && IntegerLiteralAST::convertibleTo(defineRetType)) {
    emitReturn(defineRetType);
    visitExpr(stmt.value.value());
    next();
  } else if (stmt.value) {
    assert(false && "define ret type and ret value don't match");
  } else {
    emitReturn();
  }
}

void CodeGen::visitType(TypeAST &t) noexcept {
  curr().append(getLLVMType(t));
}

void CodeGen::visitVarDecl(VarDeclAST &decl) noexcept {
  const auto llvmType = getLLVMType(decl.type);
  scope->add(decl.id, decl.type);
  emitAlloca(decl.id.name,llvmType);
  if (decl.value) {
    emitStoreBegin(llvmType);
    visitExpr(decl.value.value()); 
    emitStoreEnd(llvmType, decl.id.name);
  } else if (decl.value) {
    assert(false && "var type and expr type don't match");
  }
}
  
void CodeGen::visitExpr(ExprAST &t_expr) noexcept {
  struct ExprVisitor {
    void operator()(IntegerLiteralAST &expr) const noexcept { expr.accept(codeGen); }  
    void operator()(RefExprAST &expr) const noexcept { expr.accept(codeGen); }  

    CodeGen &codeGen;
  };

  std::visit(ExprVisitor{*this}, t_expr);
}

void CodeGen::visitRefExpr(RefExprAST &expr) noexcept {
  auto t_type { scope->getType(expr.id) };
  if (!t_type) {
    logError(expr.location, "Unknown identifier: %s", expr.id.name.c_str());
    exit(1);
  }
  data.insert(data.end() - 1, "");
  emitLoadPrev(getTempLocal(), getLLVMType(t_type.value()), expr.id.name); 
  emitLocalLabel(getTempLocal());
  ++opId; // TODO: introduce better interface for this
}

void CodeGen::visitIntegerLiteral(IntegerLiteralAST &lit) noexcept {
  curr().append(lit.value);
}
}
