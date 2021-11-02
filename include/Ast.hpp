//
// Created by vadi on 10/21/21.
//

#ifndef MINX_AST_HPP
#define MINX_AST_HPP

#include "Token.hpp"
#include "VariantsAST.hpp"
#include "FileLocation.hpp"
#include "CodeGen.hpp"
#include "ScopeCreator.hpp"

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
  virtual void accept(ScopeCreator &) noexcept = 0;
  virtual ~NodeAST() = default;
};

struct TypeAST : NodeAST {
  std::vector<Token> value;

  void accept(CodeGen &gen) noexcept override { gen.visitType(*this); }
  void accept(ScopeCreator &gen) noexcept override { gen.visitType(*this); }
};

struct IntegerLiteralAST : NodeAST {
  std::string value;

  explicit IntegerLiteralAST(std::string_view t_value) noexcept : value(t_value) {}
  void accept(CodeGen &gen) noexcept override { gen.visitIntegerLiteral(*this); }
  void accept(ScopeCreator &gen) noexcept override { gen.visitIntegerLiteral(*this); }
  static bool convertibleTo(std::string_view t_llvmtype) noexcept {
    return t_llvmtype.starts_with('i'); 
  } 
};

struct IdentifierAST : NodeAST {
  std::string name;

  explicit IdentifierAST(std::string_view t_name = "") noexcept : name(t_name) {}
  void accept(CodeGen &gen) noexcept override { gen.visitIdentifier(*this); }
  void accept(ScopeCreator &gen) noexcept override { gen.visitIdentifier(*this); }

  [[nodiscard]] auto operator<=>(const IdentifierAST &t_rhs) const noexcept {
    return name <=> t_rhs.name;
  }
};

struct RefExprAST : NodeAST {
  IdentifierAST id;

  explicit RefExprAST(const IdentifierAST &t_id) noexcept : id(t_id) {}

  void accept(CodeGen &gen) noexcept override { gen.visitRefExpr(*this); }
  void accept(ScopeCreator &gen) noexcept override { gen.visitRefExpr(*this); }
};

struct ReturnStmtAST : NodeAST {
  std::optional<ExprAST> value;

  void accept(CodeGen &gen) noexcept override { gen.visitReturnStmt(*this); }
  void accept(ScopeCreator &gen) noexcept override { gen.visitReturnStmt(*this); }
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
  void accept(ScopeCreator &vis) noexcept override { vis.visitVarDecl(*this); }
};

template <typename Visitor>
struct StatementVisitor {
  void operator()(std::monostate) {}
  void operator()(ReturnStmtAST &stmt) const noexcept { stmt.accept(vis); }
  void operator()(VarDeclAST &decl) const noexcept { decl.accept(vis); }

  Visitor &vis;
};

struct CompoundStmtAST : NodeAST {
  std::vector<StatementAST> statements;

  void accept(CodeGen &codeGen) noexcept override {
    codeGen.visitCompoundStmt(*this);
    for (auto &i : statements) {
      std::visit(StatementVisitor<CodeGen>{codeGen}, i);
    }
    codeGen.visitCompoundStmtExit(*this);
  }

  void accept(ScopeCreator &vis) noexcept override {
    vis.visitCompoundStmt(*this);
    for (auto &i: statements) {
      std::visit(StatementVisitor<ScopeCreator>{vis}, i);
    }
    vis.visitCompoundStmtExit(*this);
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

  void accept(ScopeCreator &vis) noexcept override {
    vis.visitFuncDecl(*this);     
    body.accept(vis);
  }
};


struct TranslationUnitAST : NodeAST {
  std::vector<FuncDeclAST> funcDecls;

  void accept(CodeGen &codeGen) noexcept override {
    codeGen.visitTranslationUnit(*this);
    for (auto &i : funcDecls) {
      i.accept(codeGen);
    }
    codeGen.visitTranslationUnitExit(*this);
  }

  void accept(ScopeCreator &vis) noexcept override {
    vis.visitTranslationUnit(*this);     
    for (auto &i : funcDecls) { i.accept(vis); }
    vis.visitTranslationUnitExit(*this);     
  }
};

} // namespace minx

#endif // MINX_AST_HPP
