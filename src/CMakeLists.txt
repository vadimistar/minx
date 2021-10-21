cmake_minimum_required(VERSION 3.10)
add_executable(minx main.cpp ../include/Token.hpp Lexer.cpp ../include/Lexer.hpp ../include/FileLocation.hpp ../include/Io.hpp Io.cpp)
