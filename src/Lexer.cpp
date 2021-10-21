//
// Created by vadi on 10/21/21.
//

#include "Lexer.hpp"

namespace minx {
Lexer &Lexer::move() noexcept {
  if (m_curr != m_data.end()) {
    ++m_curr;
  }
  if (m_next != m_data.end()) {
    ++m_next;
  }
  if (!isEnd()) {
    if (current() == '\n') {
      constexpr auto startColumn = 1;
      ++location.line;
      location.column = startColumn;
    } else {
      ++location.column;
    }
  }
  return *this;
}

Token Lexer::getToken() noexcept {
  const auto isWs = [](char ch) {
    return ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r';
  };
  const auto skipWs = [this, &isWs]() {
    moveWhile([&isWs, this]() { return isWs(current()); });
  };
  const auto skipComments = [this]() {
    if (current() == '/') {
      if (next() == '/') {
        moveWhile([this] () { return current() != '\n'; });
      } else {
        logError(location, "Expected '/' or '*' after '/', but got '%c'",
                 next());
      }
    }
  };
  const auto createToken = [this](TokenKind t_kind) -> Token {
    move();
    return {t_kind, ""};
  };
  const auto createWord = [this]() -> Token {
    std::string t_value;
    for (; std::isalnum(current()) || current() == '_'; move()) {
      t_value.push_back(current());
    }
    return {TokenKind::Word, t_value};
  };
  const auto createNumber = [this]() -> Token {
    std::string t_value;
    const auto parseDigits = [&t_value, this]() {
      for (; std::isdigit(current()); move()) {
        t_value.push_back(current());
      }
    };
    parseDigits();
    if (current() == '.') {
      t_value.push_back('.');
      move();
      parseDigits();
      return {TokenKind::Float, t_value};
    }
    return {TokenKind::Integer, t_value};
  };
  skipWs();
  skipComments();
  if (isEnd()) {
    return {TokenKind::Eof, ""};
  }
  switch (current()) {
  case '\n':
    move();
    return getToken();
  case '=':
    return createToken(TokenKind::Assign);
  case ';':
    return createToken(TokenKind::Semicolon);
  default:
    if (std::isalpha(current())) {
      return createWord();
    } else if (std::isdigit(current())) {
      return createNumber();
    }
    logError(location, "Unknown character: %c", current());
    exit(1);
  }
}

} // namespace minx