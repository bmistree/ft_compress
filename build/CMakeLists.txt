
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
set(TEST_FOLDER "../test/")
set(UTIL_FOLDER "../util/")
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

set(
  UTIL_HEADERS
  "${UTIL_FOLDER}/populate_random_table.hpp")

add_library(
  UTIL_LIB
  "${UTIL_FOLDER}/populate_random_table.cpp")


project (create_entries)
add_executable(create_entries "${TEST_FOLDER}/create_entries.cpp" ${LIB_HEADERS})
target_link_libraries(create_entries COMPRESS_LIB)

project (sort_table)
add_executable(sort_table "${TEST_FOLDER}/sort_table.cpp" ${LIB_HEADERS})
target_link_libraries(sort_table COMPRESS_LIB)

project (header_superset)
add_executable(header_superset "${TEST_FOLDER}/header_superset.cpp" ${LIB_HEADERS})
target_link_libraries(header_superset COMPRESS_LIB)

project (eclipse_filter)
add_executable(eclipse_filter "${TEST_FOLDER}/eclipse_filter.cpp" ${LIB_HEADERS})
target_link_libraries(eclipse_filter COMPRESS_LIB)

project (split_random)
add_executable(split_random "${TEST_FOLDER}/split_random.cpp" ${LIB_HEADERS})
target_link_libraries(split_random COMPRESS_LIB)

project (merge_random)
add_executable(merge_random "${TEST_FOLDER}/merge_random.cpp" ${LIB_HEADERS})
target_link_libraries(merge_random COMPRESS_LIB)

project (priority_random)
add_executable(priority_random "${TEST_FOLDER}/priority_random.cpp" ${LIB_HEADERS})
target_link_libraries(priority_random COMPRESS_LIB)

project (table_random)
add_executable(table_random "${TEST_FOLDER}/table_random.cpp" ${LIB_HEADERS} ${UTIL_HEADERS})
target_link_libraries(table_random COMPRESS_LIB UTIL_LIB)
