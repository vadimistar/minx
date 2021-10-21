#include "../include/Io.hpp"
#include "../include/Lexer.hpp"
#include <cassert>

int main(int argc, char **argv) {
  using namespace minx;

  const auto printHelp = [argv] () {
    std::fprintf(stdout,  "Minx compiler (version 0.1):\n"
                          "USAGE:\n"
                          "    %s [.minx source files]\n"
                , argv[0]);
  };

  if (argc == 1) {
    printHelp();
    std::fprintf(stderr, "Error: No input files provided\n");
    exit(1);
  } else if (argc > 2) {
    assert(0 && "multiple files compilation not implemented yet\n");
  }
  auto fileData { readFile(argv[1]) };
  if (!fileData) {
    printHelp();
    std::fprintf(stderr, "Error: Input file can't be opened\n");
    exit(1);
  }
  [[maybe_unused]] Lexer lexer(argv[1], fileData.value());
}