cmake_minimum_required(VERSION 3.16)

project(JV-COMPILER)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 99)
set(CMAKE_POSITION_INDEPENDENT_CODE)
SET(CMAKE_CXX_FLAGS  "-fPIE")

set(COMPILER_SOURCE_DIR  ${PROJECT_SOURCE_DIR}/source/compiler)

set(COMPILER_INCLUDES "")
set(COMPILER_SOURCES "")

set(PARSER_FILE   ${COMPILER_SOURCE_DIR}/parser/parser.y)
set(CODEGEN_DIR   ${COMPILER_SOURCE_DIR}/parser)

find_package(FLEX REQUIRED)
find_package(BISON REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "USING LLVMINCLUDE_DIR: ${LLVM_INCLUDE_DIRS}")

include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

BISON_TARGET(
  Parser
  ${COMPILER_SOURCE_DIR}/parser/parser.y
  ${CODEGEN_DIR}/parser.cpp
  COMPILE_FLAGS -v
  DEFINES_FILE ${CODEGEN_DIR}/parser.hpp
)

FLEX_TARGET(
  Scanner
  ${COMPILER_SOURCE_DIR}/parser/scanner.l
  ${CODEGEN_DIR}/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(jvc
  ${COMPILER_SOURCE_DIR}/main.cpp
  ${BISON_Parser_OUTPUTS}
  ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(jvc PRIVATE
  source/compiler
)

llvm_map_components_to_libnames(llvm_libs support core irreader passes) #new passes

target_link_libraries(jvc
  PUBLIC
    ${llvm_libs}
    fmt
    spdlog
)
add_subdirectory(third_party)
add_subdirectory(source)

enable_testing()
add_subdirectory(test)