//
// Created by vadi on 10/21/21.
//
#include "../include/Parser.hpp"
#include <cassert>

namespace minx {
DeclVector Parser::parseTranslationUnitDecl() noexcept {
  DeclVector decls;
  while (current().kind != TokenKind::Eof) {
    decls.emplace_back(parseDecl());
  }
  return decls;
}
std::unique_ptr<Decl> Parser::parseDecl() noexcept {
  switch (current().kind) {
  case TokenKind::Word:
    if (current().value == "var") {
      return parseVarDecl();
    } if (current().value == "func") {
      return parseFuncDecl();
    }
    logError(location(), "Unknown declaration (starts with '%s')",
             current().value.c_str());
    exit(1);
  case TokenKind::Semicolon:
    logWarning(location(), "Empty declaration");
    move();
    return std::make_unique<Decl>();
  default:
    logError(location(), "Unknown declaration (starts with %s)",
             tokenKindAsStr(current().kind).data());
    exit(1);
  }
}
std::unique_ptr<Expr> Parser::parseExpr() noexcept {
  switch (current().kind) {
  case TokenKind::Integer:
    return parseIntLiteralExpr();
  case TokenKind::Float:
    return parseFloatLiteralExpr();
  default:
    logError(location(), "Unknown expression (starts with %s)",
             tokenKindAsStr(current().kind));
    exit(1);
  }
}
std::unique_ptr<IntLiteralExpr> Parser::parseIntLiteralExpr() noexcept {
  assert(current().kind == TokenKind::Integer &&
         "Int literal can't be created from non-word");
  auto ret{std::make_unique<IntLiteralExpr>()};
  ret->value = current().value;
  move();
  return ret;
}
std::unique_ptr<FloatLiteralExpr> Parser::parseFloatLiteralExpr() noexcept {
  assert(current().kind == TokenKind::Float &&
         "Float literal can't be created from non-float");
  auto ret {std::make_unique<FloatLiteralExpr>()};
  ret->value = current().value;
  move();
  return ret;
}
std::unique_ptr<VarDecl> Parser::parseVarDecl() noexcept {
  matchKeyword("var");
  auto ret{std::make_unique<VarDecl>()};
  ret->name = parseName("Expected name of the variable, but got %s");
  ret->type = getPrimitiveType(parseName("Expected valid data type, but got %s"));
  if (ret->type == PrimitiveType::Null) {
    logError(location(), "Invalid data type: %s", current().value.c_str());
    exit(1);
  }
  switch (current().kind) {
  case TokenKind::Assign:
    ret->value = move().parseExpr();
    break;
  case TokenKind::Semicolon:
    ret->value = std::nullopt;
    break;
  default:
    logError(location(), "Expected '=' or ';', but got %s",
             tokenKindAsStr(current().kind).data());
    exit(1);
  }
  match(TokenKind::Semicolon);
  return ret;
}
std::string Parser::parseName(const char *t_msg = "Expected name, but got %s") noexcept {
  if (current().kind != TokenKind::Word) {
    logError(location(), t_msg,
             tokenKindAsStr(current().kind).data());
    exit(1);
  }
  std::string ret { current().value };
  move();
  return ret;
}
std::unique_ptr<FuncDecl> Parser::parseFuncDecl() noexcept {
  matchKeyword("func");
  auto ret{std::make_unique<FuncDecl>()};
  ret->name = parseName("Expected name of the function, but got %s");
  match(TokenKind::LParen);
  match(TokenKind::RParen);
  match(TokenKind::ThinArrow);
  ret->type = getPrimitiveType(parseName("Expected valid return data type, but got %s"));
  if (ret->type == PrimitiveType::Null) {
    logError(location(), "Invalid return data type: %s", current().value.c_str());
    exit(1);
  }
  match(TokenKind::LBrace);
  while (current().kind != TokenKind::RBrace) {
    ret->body.emplace_back(parseStmt());
  }
  match(TokenKind::RBrace);
  return ret;
}
std::unique_ptr<Stmt> Parser::parseStmt() noexcept {
  switch (current().kind) {
  case TokenKind::Word:
    if (current().value == "return") {
      return parseReturnStmt();
    }
    return parseDecl();
  default:
    logError(location(), "Unknown statement (starts with %s)",
             tokenKindAsStr(current().kind).data());
    exit(1);
  }
}
std::unique_ptr<ReturnStmt> Parser::parseReturnStmt() noexcept {
  matchKeyword("return");
  auto ret { std::make_unique<ReturnStmt>() };
  ret->value = parseExpr();
  match(TokenKind::Semicolon);
  return ret;
}
} // namespace minx
