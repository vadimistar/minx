//
// Created by vadi on 10/21/21.
//
#include "../include/Parser.hpp"
#include "../include/Type.hpp"

#include <optional>

namespace minx {

IdentifierAST Parser::parseIdentifier() noexcept {
  if (current().kind != TokenKind::Word) {
    logError(location(), "Can't create identifier from a %s",
             tokenKindAsStr(current().kind).data());
    exit(1);
  }
  move();
  return {IdentifierAST{.name = current().value}};
}

TypeAST Parser::parseType() noexcept {
  return parsePrimitiveType();
}

PrimitiveTypeAST Parser::parsePrimitiveType() noexcept {
  if (current().kind != TokenKind::Word) {
    logError(location(), "Expected valid data type, but got %s", tokenKindAsStr(current().kind).data());
    exit(1);
  }
  auto ret{PrimitiveTypeAST{.type = getPrimitiveType(current().value)}};
  if (ret.type == PrimitiveType::Null) {
    logError(location(), "Invalid data type: %s", current().value.c_str());
    exit(1);
  }
  move();
  return ret;
}

IntegerLiteralAST Parser::parseIntegerLiteral() noexcept {
  auto ret { IntegerLiteralAST {current().value} };
  match(TokenKind::Integer);
  return ret;
}

StatementAST Parser::parseReturnStmt() noexcept {
  matchKeyword("return");
  auto ret { ReturnStmt { std::nullopt } };
  switch (current().kind) {
  case TokenKind::Semicolon:
    break;
  case TokenKind::Integer:
    ret.value = parseIntegerLiteral();
    break;
  default:
    logError(location(), "Unknown expression in the return statement");
    exit(1);
  }
  match(TokenKind::Semicolon);
  return ret;
}

StatementAST Parser::parseStatement() noexcept {
  auto stmt { StatementAST{} };
  switch (current().kind) {
  case TokenKind::Word:
    stmt = parseReturnStmt();
    break;
  case TokenKind::Semicolon:
    move();
    break;
  default:
    logError(location(), "Unknown statement");
    exit(1);
  }
  return stmt;
}

CompoundStmt Parser::parseCompoundStmt() noexcept {
  match(TokenKind::LBrace);
  auto res { CompoundStmt {} };
  while (current().kind != TokenKind::RBrace) {
    res.statements.emplace_back(parseStatement());
  }
  move();
  return res;
}

FuncDeclAST Parser::parseFuncDecl() noexcept {
  matchKeyword("func");
  auto res {
      FuncDeclAST {}
  };
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

} // namespace minx