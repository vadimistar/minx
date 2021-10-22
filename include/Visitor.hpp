//
// Created by vadi on 10/22/21.
//

#ifndef MINX_VISITOR_HPP
#define MINX_VISITOR_HPP

#include <cassert>
#include <cstdint>
#include <string>

namespace minx {

struct Expr;
struct Stmt;
struct Decl;
struct VarDecl;
struct FuncDecl;
struct IntLiteralExpr;
struct FloatLiteralExpr;
struct ReturnStmt;

struct Visitor {
  virtual void visit(Expr *) = 0;
  virtual void visit(Stmt *) = 0;
  virtual void visit(Decl *) = 0;
  virtual void visit(VarDecl *) = 0;
  virtual void visit(FuncDecl *) = 0;
  virtual void visit(IntLiteralExpr *) = 0;
  virtual void visit(FloatLiteralExpr *) = 0;
  virtual void visit(ReturnStmt *) = 0;
};

struct Generator : Visitor {
  void visit(Expr *) noexcept override { assert(0 && "Null expr"); }
  void visit(Stmt *) noexcept override {
  }
  void visit(Decl *) noexcept override {
  }
  void visit(VarDecl *) noexcept override {

  }
  void visit(FuncDecl *) noexcept override {
  }
  void visit(IntLiteralExpr *) noexcept override {}
  void visit(FloatLiteralExpr *) noexcept override {}
  void visit(ReturnStmt *) noexcept override {}

  std::string data;
  PrimitiveType expectedType {PrimitiveType::Null};

  template <typename ... Args>
  void append(const char *t_fmt, Args ... args) noexcept {
    constexpr auto maxBuffer { 128u };
    char buff[maxBuffer];
    sprintf(buff, t_fmt, args...);
    data.append(buff);
  }
};

} // namespace minx

#endif // MINX_VISITOR_HPP
