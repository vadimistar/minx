//
// Created by vadi on 10/21/21.
//

#ifndef MINX_TOKEN_HPP
#define MINX_TOKEN_HPP

#include <string>

namespace minx {

enum struct TokenKind {
  Eof, Integer, Float, Word, Assign, Semicolon,
};

struct Token {
  TokenKind kind;
  std::string value;
};

}

#endif // MINX_TOKEN_HPP
