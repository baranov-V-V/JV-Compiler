cmake_minimum_required(VERSION 3.16)

function(add_compiler_test name)
  set(sources ${name}.cpp ${ARGN})
  set(libs gtest_main ${llvm_libs} fmt spdlog)
  
  add_executable(${name} ${sources})

  target_include_directories(${name}
    PUBLIC
      ${COMPILER_INCLUDES}
      ${COMPILER_SOURCES}
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

