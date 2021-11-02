//
// Created by vadi on 10/31/21.
//

#ifndef MINX_SCOPE_HPP
#define MINX_SCOPE_HPP

#include "Ast.hpp"
#include <map>

namespace minx {

struct Scope {
  struct IdAttr {
    bool callable { false };  
    TypeAST type;
  };

  std::map<IdentifierAST, IdAttr> data;
  Scope *prev{nullptr};

  explicit Scope() noexcept = default;
  explicit Scope(Scope *t_scope) noexcept : prev(t_scope) {}

  Scope &add(const IdentifierAST &t_id, bool t_is_callee, const TypeAST &t_type) noexcept;
  std::optional<IdAttr> get(const IdentifierAST &t_id) noexcept;
};

}

#endif // MINX_SCOPE_HPP
