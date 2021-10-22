//
// Created by vadi on 10/21/21.
//

#include "../include/Type.hpp"
#include <cassert>

namespace minx {
PrimitiveType getPrimitiveType(std::string_view t_val) {
  if (t_val == "void") {
    return PrimitiveType::Void;
  } else if (t_val == "bool") {
    return PrimitiveType::Bool;
  } else if (t_val == "int32") {
    return PrimitiveType::Int32;
  }
  return PrimitiveType::Null;
}
std::string_view getLLVMType(PrimitiveType t_type) {
  assert(t_type != PrimitiveType::Null && "Null type can't be converted to LLVM type");
  switch (t_type) {
  case PrimitiveType::Void:
    return "void";
  case PrimitiveType::Bool:
    return "i1";
  case PrimitiveType::Int32:
    return "i32";
  default:
    assert(0 && "this type is not handled");
  }
}
}