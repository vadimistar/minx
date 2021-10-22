//
// Created by vadi on 10/21/21.
//

#ifndef MINX_AST_HPP
#define MINX_AST_HPP

#include "Type.hpp"
#include "Visitor.hpp"
#include <memory>
#include <optional>
#include <string>
#include <vector>

namespace minx {

struct Node {
  virtual ~Node() = default;
  virtual void accept(Generator *) = 0;
};

struct Expr : Node {
  ~Expr() override = default;
  void accept(Generator *) override {
    assert(0 && "Null expr occured");
  }
};
struct Stmt : Node {
  ~Stmt() override = default;
  void accept(Generator *) override {}
};
struct Decl : Stmt {
  ~Decl() override = default;
  void accept(Generator *) override {}
};

using DeclVector = std::vector<std::unique_ptr<Decl>>;
using StmtVector = std::vector<std::unique_ptr<Stmt>>;

struct VarDecl : Decl {
  std::string name;
  PrimitiveType type;
  std::optional<std::unique_ptr<Expr>> value;

  ~VarDecl() override = default;

  void accept(Generator *gen) noexcept override {
    gen->append("%%%s = alloca %s\n", name.c_str(), getLLVMType(type).data());
    if (value) {
      gen->append("store ");
      auto tmp { gen->expectedType };
      gen->expectedType = type;
      value.value()->accept(gen);
      gen->expectedType = tmp;
      gen->append(", %s* %%%s\n", getLLVMType(type).data(), name.c_str());
    }
  }
};

struct FuncDecl : Decl {
  std::string name;
  PrimitiveType type;
  StmtVector body;

  ~FuncDecl() override = default;

  void accept(Generator *gen) noexcept override {
    gen->append("define %s @%s() {\n", getLLVMType(type).data(), name.c_str());
    gen->expectedType = type;
    for (auto &i : body) {
      i->accept(gen);
    }
    gen->expectedType = PrimitiveType::Null;
    gen->append("}\n");
  }
};

struct IntLiteralExpr : Expr {
  std::string value;

  ~IntLiteralExpr() override = default;
  void accept(Generator *gen) noexcept override {
    gen->append("%s %s", getLLVMType(gen->expectedType).data(), value.c_str());
  }
};

struct FloatLiteralExpr : Expr {
  std::string value;

  ~FloatLiteralExpr() override = default;
  void accept(Generator *gen) noexcept override {
    gen->append("%s %s", getLLVMType(gen->expectedType).data(), value.c_str());
  }
};

struct ReturnStmt : Stmt {
  std::unique_ptr<Expr> value;

  ~ReturnStmt() override = default;
  void accept(Generator *gen) noexcept override {
    gen->append("ret ");
    value->accept(gen);
    gen->append("\n");
  }
};

} // namespace minx

#endif // MINX_AST_HPP
