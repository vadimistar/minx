//
// Created by vadi on 10/21/21.
//

#include "../include/Type.hpp"
#include "../include/Ast.hpp"
#include <cassert>

namespace minx {
std::optional<std::string_view> getPrimitiveLLVMType(std::string_view t_minx_primitive) {
  if (t_minx_primitive == "bool") {
    return "i1";
  }
  if (t_minx_primitive == "int8" ) {
    return "i8";
  }
  if (t_minx_primitive == "int16") {
    return "i16";
  }
  if (t_minx_primitive == "int32") {
    return "i32";
  }
  if (t_minx_primitive == "int64") {
    return "i64";
  }
  return std::nullopt;
}

std::string getLLVMType(const TypeAST &type) {
  std::string res {};
  for (auto i { type.value.rbegin() }; i != type.value.rend(); ++i) {
    switch (i->kind) {
      case TokenKind::Mul:
        res += '*';
        break;
      case TokenKind::Word: {
        auto prim = getPrimitiveLLVMType(i->value);
        if (!prim) {
          logError(i->location, "Expected valid primitive data type, but got %s", i->value.c_str());
          exit(1);
        }
        res += prim.value();
        } 
        break;
      default:
        assert(false && "the conversion of this token kind is not implemented");  
    }
  }
  return res;
}

}