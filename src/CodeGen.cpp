//
// Created by vadi on 10/30/21.
//

#include "../include/CodeGen.hpp"
#include "../include/Ast.hpp"

namespace minx {
void CodeGen::visitFuncDecl(FuncDeclAST &funcDecl) noexcept {
  defineRetType = getLLVMType(funcDecl.returnType);
  emitDefineHeader(defineRetType, funcDecl.id.name);
}

void CodeGen::visitReturnStmt(ReturnStmtAST & stmt) noexcept {
  if (stmt.value && IntegerLiteralAST::convertibleTo(defineRetType)) {
    emitReturn(defineRetType, stmt.value->value);
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
  emitAlloca(decl.id.name,llvmType);
  if (decl.value && IntegerLiteralAST::convertibleTo(llvmType)) {
    emitStore(llvmType, decl.value->value, decl.id.name);
  } else if (decl.value) {
    assert(false && "var type and expr type don't match");
  }
}

}
