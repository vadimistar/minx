//
// Created by vadi on 10/21/21.
//

#ifndef MINX_FILELOCATION_HPP
#define MINX_FILELOCATION_HPP

#include <cstdio>
#include <cstdint>
#include <string_view>

namespace minx {

struct FileLocation {
  using Line = std::uint32_t;
  using Column = std::uint32_t;

  std::string_view filename;
  Line line;
  Column column;

  FileLocation(std::string_view t_filename, Line t_line, Column t_col) noexcept
    : filename(t_filename), line(t_line), column(t_col) {}
};

template <typename ... Args>
void logError(FileLocation t_loc, const char* t_fmt, Args ... args) {
  std::fprintf(stderr, "%s:%u:%u: Error: ", t_loc.filename.data(), t_loc.line, t_loc.column);
  std::fprintf(stderr, t_fmt, args...);
  std::fprintf(stderr, "\n");
}

template <typename ... Args>
void logWarning(FileLocation t_loc, const char* t_fmt, Args ... args) {
  std::fprintf(stderr, "%s:%u:%u: Warning: ", t_loc.filename.data(), t_loc.line, t_loc.column);
  std::fprintf(stderr, t_fmt, args...);
  std::fprintf(stderr, "\n");
}
}

#endif // MINX_FILELOCATION_HPP
