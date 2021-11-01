//
// Created by vadi on 10/21/21.
//
#include "../include/Parser.hpp"
#include "../include/Type.hpp"

#include <optional>

namespace minx {

  // TODO: ast nodes don't hold their location

IdentifierAST Parser::parseIdentifier() noexcept {
  auto val = current().value;
  if (current().kind != TokenKind::Word) {
    logError(location(), "Can't create identifier from a %s",
             tokenKindAsStr(current().kind).data());
    exit(1);
  }
  move();
  return IdentifierAST {val};
}

TypeAST Parser::parseType() noexcept {
  TypeAST res{};
  while (current().kind != TokenKind::Word) {
    switch (current().kind) {
      case TokenKind::Mul: 
        res.value.emplace_back(current());
        break;
      default:
        logError(location(), "Expected valid data type, but got %s", tokenKindAsStr(current().kind).data());
        exit(1);
    }
    move();
  }
  res.value.emplace_back(current());
  move();
  return res;
}

IntegerLiteralAST Parser::parseIntegerLiteral() noexcept {
  IntegerLiteralAST ret{current().value};
  match(TokenKind::Integer);
  return ret;
}

StatementAST Parser::parseReturnStmt() noexcept {
  matchKeyword("return");
  auto ret { ReturnStmtAST {} };
  switch (current().kind) {
  case TokenKind::Semicolon:
    ret.value = std::nullopt;
    break;
  case TokenKind::Integer:
    ret.value = parseIntegerLiteral();
    break;
  default:
    logError(location(), "%s", "Unknown expression in the return statement");
    exit(1);
  }
  match(TokenKind::Semicolon);
  return ret;
}

StatementAST Parser::parseStatement() noexcept {
  auto stmt { StatementAST{} };
  switch (current().kind) {
  case TokenKind::Word:
    if (current().value == "return") {
      stmt = parseReturnStmt();
    } else if (current().value == "var") {
      stmt = parseVarDecl();
    }
    break;
  case TokenKind::Semicolon:
    move();
    break;
  default:
    logError(location(), "%s", "Unknown statement");
    exit(1);
  }
  return stmt;
}

CompoundStmtAST Parser::parseCompoundStmt() noexcept {
  match(TokenKind::LBrace);
  auto res { CompoundStmtAST {} };
  while (current().kind != TokenKind::RBrace) {
    res.statements.emplace_back(parseStatement());
  }
  move();
  return res;
}

FuncDeclAST Parser::parseFuncDecl() noexcept {
  matchKeyword("func");
  FuncDeclAST res;
  res.id = parseIdentifier();
  match(TokenKind::LParen);
  match(TokenKind::RParen);
  match(TokenKind::ThinArrow);
  res.returnType = parseType();
  res.body = parseCompoundStmt();
  return res;
}

TranslationUnitAST Parser::parseTranslationUnit() noexcept {
  auto res { TranslationUnitAST{} };
  while (current().kind != TokenKind::Eof) {
    res.funcDecls.emplace_back(parseFuncDecl());
  }
  return res;
}
VarDeclAST Parser::parseVarDecl() noexcept {
  matchKeyword("var");
  VarDeclAST res;
  res.id = parseIdentifier();
  match(TokenKind::Colon);
  res.type = parseType();
  if (current().kind == TokenKind::Assign) {
    move();
    res.value = parseIntegerLiteral();
  }
  match(TokenKind::Semicolon);
  return res;
}

} // namespace minx