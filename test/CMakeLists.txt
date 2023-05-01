cmake_minimum_required(VERSION 3.16)

add_library(jvc_lib)

set(libs ${llvm_libs} fmt spdlog scn::scn)

file(GLOB_RECURSE COMPILER_INCLUDES CONFIGURE_DEPENDS ${COMPILER_SOURCE_DIR}/*.hpp)
file(GLOB_RECURSE COMPILER_SOURCES CONFIGURE_DEPENDS ${COMPILER_SOURCE_DIR}/*.cpp)

#message(STATUS "includes test: ${COMPILER_INCLUDES}")
#message(STATUS "sources test:  ${COMPILER_SOURCES}")

target_include_directories(jvc_lib
  PUBLIC
    ${COMPILER_SOURCE_DIR}/.
  )

target_sources(jvc_lib
  PUBLIC
    ${COMPILER_INCLUDES}
  PRIVATE
    ${COMPILER_SOURCES}
  )

target_link_libraries(jvc_lib PUBLIC ${libs})

function(add_compiler_test name)
  set(sources 
    test_main.cpp
    util/output_buffer.cpp
    ${name}.cpp 
    ${ARGN}
  )
  set(libs gtest jvc_lib)
  
  add_executable(${name} ${sources})

  target_include_directories(${name}
    PUBLIC
      ${COMPILER_SOURCE_DIR}/.
      ${CMAKE_CURRENT_LIST_DIR}/.
    )
  
  target_link_libraries(${name} PUBLIC ${libs})

  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_compiler_test(test_interpreter)
add_compiler_test(test_ir)