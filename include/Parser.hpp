//
// Created by vadi on 10/21/21.
//

#ifndef MINX_PARSER_HPP
#define MINX_PARSER_HPP

#include "Lexer.hpp"
#include "Ast.hpp"

namespace minx {
  class Parser {
    Token m_token;
    Lexer &m_lexer;

    [[nodiscard]] auto location() const noexcept {
      return m_lexer.location;
    }

  public:
    explicit Parser(Lexer& t_lexer) noexcept
    : m_token(t_lexer.getToken()), m_lexer(t_lexer) {}

    [[nodiscard]] const Token& current() const noexcept {
      return m_token;
    }
    Parser& move() noexcept { m_token = m_lexer.getToken();
      return *this;
    }
    [[nodiscard]] const Token& next() noexcept {
      move();
      return m_token;
    }
    Parser& match(TokenKind t_kind) noexcept {
      if (t_kind != current().kind) {
        logError(location(), "Expected %s, but got %s", tokenKindAsStr(t_kind).data(),
                 tokenKindAsStr(current().kind).data());
        exit(1);
      }
      move();
      return *this;
    }
    [[nodiscard]] const Token& nextAssert(TokenKind t_kind) noexcept {
      return match(t_kind).current();
    }
    Parser& matchKeyword(std::string_view t_value) noexcept {
      if (current().kind != TokenKind::Word) {
        logError(location(), "Expected '%s', but got %s", t_value.data(),
                 tokenKindAsStr(current().kind).data());
        exit(1);
      } else if (t_value != current().value) {
        logError(location(), "Expected '%s', but got '%s'", t_value.data(),
                 current().value.c_str());
        exit(1);
      }
      move();
      return *this;
    }
    [[nodiscard]] const Token& nextAssertKeyword(std::string_view t_value) noexcept {
      return matchKeyword(t_value).current();
    }
    DeclVector parseTranslationUnitDecl() noexcept;
    std::unique_ptr<Decl> parseDecl() noexcept;
    std::unique_ptr<Stmt> parseStmt() noexcept;
    std::unique_ptr<Expr> parseExpr() noexcept;
    std::unique_ptr<VarDecl> parseVarDecl() noexcept;
    std::unique_ptr<FuncDecl> parseFuncDecl() noexcept;
    std::unique_ptr<IntLiteralExpr> parseIntLiteralExpr() noexcept;
    std::unique_ptr<FloatLiteralExpr> parseFloatLiteralExpr() noexcept;
    std::unique_ptr<ReturnStmt> parseReturnStmt() noexcept;

    std::string parseName(const char* t_fmt) noexcept;
  };
}

#endif // MINX_PARSER_HPP
