//
// Created by vadi on 10/21/21.
//

#ifndef MINX_IO_HPP
#define MINX_IO_HPP

#include <optional>
#include <string>

namespace minx {
std::optional<std::string> readFile(const char* t_fileName);
}

#endif // MINX_IO_HPP
