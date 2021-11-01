//
// Created by vadi on 10/21/21.
//

#ifndef MINX_TYPE_HPP
#define MINX_TYPE_HPP

#include "Ast.hpp"
#include <string_view>

namespace minx {

std::string getLLVMType(const TypeAST &);
std::optional<std::string_view> getPrimitiveLLVMType(std::string_view t_minx_primitive);

}

#endif // MINX_TYPE_HPP
