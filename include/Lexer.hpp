//
// Created by vadi on 10/21/21.
//

#ifndef MINX_LEXER_HPP
#define MINX_LEXER_HPP

#include "FileLocation.hpp"
#include "Token.hpp"
#include <string_view>
#include <concepts>

namespace minx {

class Lexer {
  const std::string_view m_data;
  std::string_view::iterator m_curr;
  std::string_view::iterator m_next;

public:
  FileLocation location;

  [[nodiscard]] auto current() const noexcept { return *m_curr; }
  [[nodiscard]] auto next() const noexcept { return *m_next; }
  [[nodiscard]] auto isEnd() const noexcept { return m_next == m_data.end(); }

  Lexer(std::string_view t_filename, std::string_view t_data) noexcept
      : m_data(t_data), m_curr(m_data.begin()),
        m_next((m_data.begin() != m_data.end()) ? m_data.begin() + 1
                                                : m_data.begin()),
        location(t_filename, 1, 1) {}
  Lexer &move() noexcept;

  template <typename Pred> requires std::predicate<Pred>
  Lexer& moveWhile(Pred t_predicate) noexcept {
    while (!isEnd() && t_predicate()) {
      move();
    }
    return *this;
  }

  Token getToken() noexcept;
};

}

#endif // MINX_LEXER_HPP
