file(GLOB_RECURSE COMPILER_INCLUDES *.hpp)
file(GLOB_RECURSE COMPILER_SOURCES *.cpp)

target_include_directories(compiler
  PUBLIC
    .
)

target_sources(compiler
  PUBLIC
    ${COMPILER_INCLUDES}
    #${MINI_COMPILER_SOURCE_DIR}/parser/location.hh
  PRIVATE
    ${COMPILER_SOURCES}
)