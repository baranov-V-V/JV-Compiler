cmake_minimum_required(VERSION 3.16)

function(add_compiler_test name)
  set(sources ${name}.cpp ${ARGN})
  set(libs gtest_main ${llvm_libs} fmt spdlog)
  
  add_executable(${name} ${sources})

  file(GLOB_RECURSE COMPILER_INCLUDES CONFIGURE_DEPENDS ${COMPILER_SOURCE_DIR}/*.hpp)
  file(GLOB_RECURSE COMPILER_SOURCES CONFIGURE_DEPENDS ${COMPILER_SOURCE_DIR}/*.cpp)

  message(STATUS "includes test: ${COMPILER_INCLUDES}")
  message(STATUS "sources test:  ${COMPILER_SOURCES}")

  target_include_directories(${name}
    PUBLIC
      ${COMPILER_SOURCE_DIR}/.
  )

  target_sources(${name}
    PUBLIC
      ${COMPILER_INCLUDES}
    PRIVATE
      ${COMPILER_SOURCES}
  )
  
  target_link_libraries(${name} PUBLIC ${libs})

  add_test(NAME ${name} COMMAND ${name})
endfunction()

add_compiler_test(test_interpreter)
add_compiler_test(test_ir)