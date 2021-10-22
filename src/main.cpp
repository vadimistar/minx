#include "../include/Io.hpp"
#include "../include/Lexer.hpp"
#include <Parser.hpp>

int main(int argc, char **argv) {
  using namespace minx;

  const auto printHelp = [argv]() {
    std::fprintf(stdout,
                 "Minx compiler (version 0.1):\n"
                 "USAGE:\n"
                 "    %s [.minx source files]\n"
                 ,
                 argv[0]);
  };

  const auto error = [&printHelp] (const char* t_msg) {
    printHelp();
    std::fprintf(stderr, "%s", t_msg);
    exit(1);
  };

  if (argc == 1) {
    error("Error: No input files provided\n");
  } else if (argc > 2) {
    assert(0 && "multiple files compilation is unavailable.");
  }

  if (!std::string_view{argv[1]}.ends_with(".minx")) {
    printHelp();
    std::fprintf(stderr, "Error: %s: incorrect extension of the file (must be .minx)", argv[1]);
  }
  auto fileData{readFile(argv[1])};
  if (!fileData) {
    printHelp();
    std::fprintf(stderr, "Error: Input file can't be opened\n");
    exit(1);
  }
  Lexer lexer(argv[1], fileData.value());
  Parser parser(lexer);
  auto unit = parser.parseTranslationUnitDecl();
  auto gen { std::make_unique<Generator>() };
  for (auto &i: unit) {
    i->accept(gen.get());
  }
  std::string newFileName { argv[1] };
  newFileName.erase(newFileName.size() - 5);
  constexpr auto maxBuff = 256u;
  char buff[maxBuff];
  sprintf(buff, "%s.ll", newFileName.c_str());
  writeFile(buff, gen->data);
  sprintf(buff, "llvm-as %s.ll -o %s.bc; "
                "llc -filetype=obj %s.bc; "
                "gcc -no-pie %s.o -o %s;"
                "rm %s.o; rm %s.bc", newFileName.c_str(),
          newFileName.c_str(), newFileName.c_str(), newFileName.c_str(),
          newFileName.c_str(), newFileName.c_str(), newFileName.c_str());
  system(buff);
}