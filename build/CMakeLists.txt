
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

set(TEST_FOLDER "../test/")
set(LIB_FOLDER "../lib/")
set(
  LIB_HEADERS
  "${LIB_FOLDER}/action.hpp"
  "${LIB_FOLDER}/header.hpp"
  "${LIB_FOLDER}/entry.hpp"
  "${LIB_FOLDER}/table.hpp")

add_library(
  COMPRESS_LIB
  "${LIB_FOLDER}/action.cpp"
  "${LIB_FOLDER}/header.cpp"
  "${LIB_FOLDER}/entry.cpp"
  "${LIB_FOLDER}/table.cpp")

project (create_entries)
add_executable(create_entries "${TEST_FOLDER}/create_entries.cpp" ${LIB_HEADERS})
target_link_libraries(create_entries COMPRESS_LIB)
