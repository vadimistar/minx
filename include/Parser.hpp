//
// Created by vadi on 10/21/21.
//

#ifndef MINX_PARSER_HPP
#define MINX_PARSER_HPP

#include "Ast.hpp"
#include "Lexer.hpp"

namespace minx {
class Parser {
  std::vector<Token> m_tokens;
  decltype(m_tokens)::const_iterator m_iterator;

  [[nodiscard]] auto location() const noexcept { return m_iterator->location; }

public:
  explicit Parser(Lexer &t_lexer) noexcept {
    for (auto tok { t_lexer.getToken() }; tok.kind != TokenKind::Eof; tok = t_lexer.getToken()) {
      m_tokens.emplace_back(tok);
    }
    m_tokens.emplace_back(Token {
        .kind = TokenKind::Eof,
        .value = "",
        .location = m_tokens.back().location,
    });
    m_iterator = m_tokens.cbegin();
  }

  using PeekOffset = std::uint32_t;

  [[nodiscard]] const Token &peek(PeekOffset offset) const noexcept {
    if (offset > (m_tokens.cend() - m_iterator - 1)) {
      return m_tokens.back();
    }
    return *(m_iterator + offset);
  }

  [[nodiscard]] const Token &current() const noexcept { return peek(0); }

  Parser &move() noexcept {
    ++m_iterator;
    return *this;
  }

  [[nodiscard]] const Token &next() noexcept {
    move();
    return current();
  }

  Parser &match(TokenKind t_kind) noexcept {
    if (t_kind != current().kind) {
      logError(location(), "Expected %s, but got %s",
               tokenKindAsStr(t_kind).data(),
               tokenKindAsStr(current().kind).data());
      exit(1);
    }
    move();
    return *this;
  }

  Parser &matchKeyword(std::string_view t_value) noexcept {
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

  IdentifierAST parseIdentifier() noexcept;
  TypeAST parseType() noexcept;
  IntegerLiteralAST parseIntegerLiteral() noexcept;
  StatementAST parseReturnStmt() noexcept;
  StatementAST parseStatement() noexcept;
  CompoundStmtAST parseCompoundStmt() noexcept;
  FuncDeclAST parseFuncDecl() noexcept;
  VarDeclAST parseVarDecl() noexcept;
  TranslationUnitAST parseTranslationUnit() noexcept;
};
} // namespace minx

#endif // MINX_PARSER_HPP
