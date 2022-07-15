# googletest requires at least C++11
set(CMAKE_CXX_STANDARD 11)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(modern_test modern_test.cc)
target_link_libraries(modern_test gtest_main modern_lib)
target_include_directories(modern_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(noerr_test noerr_test.cc)
target_link_libraries(noerr_test gtest_main noerr_lib)
target_include_directories(noerr_test PUBLIC ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(modern_test)
gtest_discover_tests(noerr_test)
