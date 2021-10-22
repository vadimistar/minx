//
// Created by vadi on 10/21/21.
//
#include <Io.hpp>
#include <iostream>
#include <fstream>
#include <cstdint>

std::optional<std::string> minx::readFile(const char *t_fileName) {
  std::ifstream file(t_fileName, std::ios::in | std::ios::binary | std::ios::ate);
  if (!file.is_open()) {
    return std::nullopt;
  }
  auto fileSize { file.tellg() };
  file.seekg(0, std::ios::beg);
  std::string bytes(static_cast<std::uint32_t>(fileSize), '\0');
  file.read(bytes.data(), fileSize);
  bytes.push_back('\0');
  return bytes;
}
void minx::writeFile(const char *t_fileName, std::string_view t_data) {
  std::ofstream file {t_fileName};
  file << t_data;
}
