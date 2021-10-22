//
// Created by vadi on 10/21/21.
//

#ifndef MINX_TYPE_HPP
#define MINX_TYPE_HPP

#include <string_view>

namespace minx {

enum struct PrimitiveType {
  Null, Void, Bool, Int32,
};

PrimitiveType getPrimitiveType(std::string_view t_val);
std::string_view getLLVMType(PrimitiveType t_type);

}

#endif // MINX_TYPE_HPP
