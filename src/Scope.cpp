//
// Created by vadi on 10/31/21.
//

#include "Scope.hpp"
minx::Scope &minx::Scope::add(const minx::IdentifierAST &t_id,
                              bool t_is_callee,
                              const minx::TypeAST &t_type) noexcept {
  if (data.contains(t_id)) {
    logError(t_id.location, "%s", "Object with this identifier is already declared");
    exit(1);
  }
  data.insert({t_id, {t_is_callee, t_type}});
  return *this;
}

std::optional<minx::Scope::IdAttr> minx::Scope::get(const minx::IdentifierAST &t_id) noexcept {
  if (auto m = data.find(t_id); m == data.end()) {
    return std::nullopt;
  } else {
    return m->second;
  }
}