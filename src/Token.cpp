//
// Created by vadi on 10/21/21.
//

#include "../include/Token.hpp"
#include <cassert>

namespace minx {

std::string_view tokenKindAsStr(TokenKind t) {
  switch (t) {
  case TokenKind::Integer:
    return "integer";
  case TokenKind::Float:
    return "float";
  case TokenKind::Semicolon:
    return "';'";
  case TokenKind::Assign:
    return "'='";
  case TokenKind::Word:
    return "word";
  case TokenKind::Eof:
    return "end of file";
  case TokenKind::LParen:
    return "'('";
  case TokenKind::RParen:
    return "')'";
  case TokenKind::LBrace:
    return "'{'";
  case TokenKind::RBrace:
    return "'}'";
  case TokenKind::ThinArrow:
    return "'->'";
  case TokenKind::Mul:
    return "'*'";
  default:
    assert(0 && "This kind of token is not handled");
  }
}
}