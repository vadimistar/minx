//
// Created by vadi on 10/31/21.
//

#ifndef MINX_SCOPE_HPP
#define MINX_SCOPE_HPP

#include "Ast.hpp"
#include <map>

namespace minx {

struct Scope {
  std::map<IdentifierAST, TypeAST> data;
  Scope *prev;

  explicit Scope(Scope *t_prev = nullptr) noexcept : prev(t_prev) {}

  Scope &add(const IdentifierAST &t_id, const TypeAST &t_type) noexcept;
  std::optional<TypeAST> getType(const IdentifierAST &t_id) noexcept;
};

}

#endif // MINX_SCOPE_HPP
