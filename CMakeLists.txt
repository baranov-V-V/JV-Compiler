cmake_minimum_required(VERSION 3.16)

project(MINI_COMPILER)

set(MINI_COMPILER_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/source/compiler)

set(SCANNER_FILE  ${MINI_COMPILER_SOURCE_DIR}/parser/scanner.l)
set(PARSER_FILE   ${MINI_COMPILER_SOURCE_DIR}/parser/parser.y)
set(CODEGEN_DIR   ${MINI_COMPILER_SOURCE_DIR}/parser)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)

BISON_TARGET(
  Parser
  ${MINI_COMPILER_SOURCE_DIR}/parser/parser.y
  ${CODEGEN_DIR}/parser.cpp
  COMPILE_FLAGS -v
  DEFINES_FILE ${CODEGEN_DIR}/parser.hpp
)

FLEX_TARGET(
  Scanner
  ${MINI_COMPILER_SOURCE_DIR}/parser/scanner.l
  ${CODEGEN_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE)
SET(CMAKE_CXX_FLAGS  "-fPIE")

add_executable(
  compiler
  ${MINI_COMPILER_SOURCE_DIR}/main.cpp
  ${BISON_Parser_OUTPUTS}
  ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(compiler
  PUBLIC
    ${MINI_COMPILER_INCLUDE_DIR}
)

target_include_directories(compiler PRIVATE 
  source/compiler
)


enable_testing()
add_subdirectory(third_party)
add_subdirectory(test)

add_subdirectory(source)