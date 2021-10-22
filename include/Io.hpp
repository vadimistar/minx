//
// Created by vadi on 10/21/21.
//

#ifndef MINX_IO_HPP
#define MINX_IO_HPP

#include <optional>
#include <string>

namespace minx {
std::optional<std::string> readFile(const char* t_fileName);
void writeFile(const char* t_fileName, std::string_view t_data);
}

#endif // MINX_IO_HPP
