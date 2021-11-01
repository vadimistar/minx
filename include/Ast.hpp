//
// Created by vadi on 10/21/21.
//

#ifndef MINX_AST_HPP
#define MINX_AST_HPP

#include "Token.hpp"
#include "VariantsAST.hpp"
#include "FileLocation.hpp"
#include "CodeGen.hpp"

#include <memory>
#include <cassert>
#include <optional>
#include <string>
#include <variant>
#include <vector>

namespace minx {

struct NodeAST {
  FileLocation location{"(unknown)", 0, 0};

  virtual void accept(CodeGen &) noexcept = 0;
  virtual ~NodeAST() = default;
};

struct TypeAST : NodeAST {
  std::vector<Token> value;

  void accept(CodeGen &gen) noexcept override { gen.visitType(*this); }
};

struct IntegerLiteralAST : NodeAST {
  std::string value;

  explicit IntegerLiteralAST(std::string_view t_value) noexcept : value(t_value) {}
  void accept(CodeGen &gen) noexcept override { gen.visitIntegerLiteral(*this); }
  static bool convertibleTo(std::string_view t_llvmtype) noexcept {
    return t_llvmtype.starts_with('i'); 
  } 
};

struct IdentifierAST : NodeAST {
  std::string name;

  explicit IdentifierAST(std::string_view t_name = "") noexcept : name(t_name) {}
  void accept(CodeGen &gen) noexcept override { gen.visitIdentifier(*this); }

  [[nodiscard]] auto operator<=>(const IdentifierAST &t_rhs) const noexcept {
    return name <=> t_rhs.name;
  }
};

struct RefExprAST : NodeAST {
  IdentifierAST id;

  explicit RefExprAST(const IdentifierAST &t_id) noexcept : id(t_id) {}

  void accept(CodeGen &gen) noexcept override { gen.visitRefExpr(*this); }
};

struct ReturnStmtAST : NodeAST {
  std::optional<ExprAST> value;

  void accept(CodeGen &gen) noexcept override { gen.visitReturnStmt(*this); }
};

struct VarDeclAST : NodeAST {
  IdentifierAST id;
  TypeAST type;
  std::optional<ExprAST> value;

  explicit VarDeclAST() noexcept
      : value{std::nullopt} {}
  void accept(CodeGen &codeGen) noexcept override {
    codeGen.visitVarDecl(*this);
  }
};

struct StatementVisitor {
  void operator()(std::monostate) {}
  void operator()(ReturnStmtAST &stmt) const noexcept { stmt.accept(codeGen); }
  void operator()(VarDeclAST &decl) const noexcept { decl.accept(codeGen); }

  CodeGen &codeGen;
};

struct CompoundStmtAST : NodeAST {
  std::vector<StatementAST> statements;

  void accept(CodeGen &codeGen) noexcept override {
    codeGen.visitCompoundStmt(*this);
    for (auto &i : statements) {
      std::visit(StatementVisitor{codeGen}, i);
    }
    codeGen.emitDefineBodyEnd();
  }
};

struct FuncDeclAST : NodeAST {
  IdentifierAST id;
  TypeAST returnType;
  CompoundStmtAST body;

  void accept(CodeGen &codeGen) noexcept override {
    codeGen.visitFuncDecl(*this);
    body.accept(codeGen);
  }
};


struct TranslationUnitAST : NodeAST {
  std::vector<FuncDeclAST> funcDecls;

  void accept(CodeGen &codeGen) noexcept override {
    codeGen.visitTranslationUnit(*this);
    for (auto &i : funcDecls) {
      i.accept(codeGen);
    }
  }
};

} // namespace minx

#endif // MINX_AST_HPP
