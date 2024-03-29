# googletest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(selectionsort_tests selectionsort_tests.cc)
target_link_libraries(selectionsort_tests gtest_main selectionsort_lib)
target_include_directories(selectionsort_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(quicksort_tests quicksort_tests.cc)
target_link_libraries(quicksort_tests gtest_main quicksort_lib)
target_include_directories(quicksort_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(binarysearch_tests binarysearch_tests.cc)
target_link_libraries(binarysearch_tests gtest_main binarysearch_lib)
target_include_directories(binarysearch_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(vec_tests vec_tests.cc)
target_link_libraries(vec_tests gtest_main vec_lib)
target_include_directories(vec_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(llist_tests llist_tests.cc)
target_link_libraries(llist_tests gtest_main llist_lib)
target_include_directories(llist_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(htable_tests htable_tests.cc)
target_link_libraries(htable_tests gtest_main htable_lib)
target_include_directories(htable_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(bst_tests bst_tests.cc)
target_link_libraries(bst_tests gtest_main bst_lib)
target_include_directories(bst_tests PUBLIC ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(selectionsort_tests)
gtest_discover_tests(quicksort_tests)
gtest_discover_tests(binarysearch_tests)
gtest_discover_tests(vec_tests)
gtest_discover_tests(llist_tests)
gtest_discover_tests(htable_tests)
gtest_discover_tests(bst_tests)
