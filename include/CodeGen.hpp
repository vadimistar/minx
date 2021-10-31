//
// Created by vadi on 10/30/21.
//

#ifndef MINX_CODEGEN_HPP
#define MINX_CODEGEN_HPP

#include "Visitor.hpp"

#include <vector>
#include <string>

namespace minx {

struct CodeGen : Visitor {
  std::vector<std::string> data { {""} };

  auto &prev() noexcept {
    if (data.size() > 1) {
      return *(data.end() - 2);
    }
    return *(data.begin());
  }

  auto &curr() noexcept { return data.back(); }

  auto &next() noexcept {
    data.emplace_back("");
    return curr();
  }

  void emitGlobalLabel(std::string_view t_name) {
    curr().append("@");
    curr().append(t_name);
  }

  void emitLocalLabel(std::string_view t_name) {
    curr().append("%");
    curr().append(t_name);
  }

  void emitDefineHeader(std::string_view t_type, std::string_view t_name) {
    curr().append("define ");
    curr().append(t_type);
    curr().append(" ");
    emitGlobalLabel(t_name);
    curr().append("()");
  }

  void emitDefineBodyBegin() {
    curr().append("{");
    next();
  }

  void emitDefineBodyEnd() {
    curr().append("}");
    next();
  }

  void emitReturn(std::string_view t_type, std::string_view t_value) {
    curr().append("ret ");
    curr().append(t_type);
    curr().append(" ");
    curr().append(t_value);
    next();
  }

  void emitReturn() {
    curr().append("ret void");
    next();
  }

  void emitAlloca(std::string_view t_name, std::string_view t_type) {
    emitLocalLabel(t_name);
    curr().append(" = alloca ");
    curr().append(t_type);
    next();
  }

  void emitLoad(std::string_view t_name, std::string_view t_type, std::string_view t_src) {
    emitLocalLabel(t_name);
    curr().append(" = load ");
    curr().append(t_type);
    curr().append(", ");
    curr().append(t_type);
    curr().append("* ");
    emitLocalLabel(t_src);
    next();
  }

  void emitStore(std::string_view t_type, std::string_view t_src, std::string_view t_dst) {
    curr().append("store ");
    curr().append(t_type);
    curr().append(" ");
    curr().append(t_src);
    curr().append(", ");
    curr().append(t_type);
    curr().append("* ");
    emitLocalLabel(t_dst);
    next();
  }

  std::string defineRetType;

  void visitIdentifier(IdentifierAST &) noexcept override {}
  void visitType(TypeAST &t) noexcept override;
  void visitPrimitiveType(PrimitiveTypeAST &) noexcept override {}
  void visitPointerType(PointerTypeAST &) noexcept override {}
  void visitIntegerLiteral(IntegerLiteralAST &) noexcept override {}
  void visitStatement(StatementAST &) noexcept override {}
  void visitReturnStmt(ReturnStmtAST &) noexcept override;
  void visitCompoundStmt(CompoundStmtAST &) noexcept override {
    emitDefineBodyBegin();
  }
  void visitFuncDecl(FuncDeclAST &) noexcept override;
  void visitVarDecl(VarDeclAST &) noexcept override;
  void visitTranslationUnit(TranslationUnitAST &) noexcept override {}
};

} // namespace minx

#endif // MINX_CODEGEN_HPP
