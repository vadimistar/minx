cmake_minimum_required(VERSION 3.10)
add_executable(minx main.cpp ../include/Token.hpp Lexer.cpp ../include/Lexer.hpp ../include/FileLocation.hpp ../include/Io.hpp Io.cpp ../include/Parser.hpp Parser.cpp Token.cpp ../include/Ast.hpp ../include/Type.hpp Type.cpp ../include/Visitor.hpp)
