//
// Created by vadi on 10/21/21.
//

#ifndef MINX_TOKEN_HPP
#define MINX_TOKEN_HPP

#include "FileLocation.hpp"
#include <string>

namespace minx {

enum struct TokenKind {
  Eof, Integer, Float, Word, Assign, Semicolon,
  LParen, RParen, LBrace, RBrace, ThinArrow, Mul,
};

struct Token {
  TokenKind kind;
  std::string value;
  FileLocation location;
};

std::string_view tokenKindAsStr(TokenKind t);

}

#endif // MINX_TOKEN_HPP
