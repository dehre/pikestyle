cmake_minimum_required(VERSION 3.21)

# 
# Set the project name and version
# 
project(pikestyle VERSION 1.0)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_C_CLANG_TIDY clang-tidy)

# 
# Compiler options
# 
add_compile_options(
  -Wall
  -Wextra
  -Wcast-qual
  -Wconversion
  -Wno-sign-conversion
  -g3
  -O0
  $<$<CONFIG:RELEASE>:-g0> # overwrites -g3
  $<$<CONFIG:RELEASE>:-O3> # overwrites -O0
  $<$<CONFIG:ASAN>:-fsanitize=address>
  $<$<CONFIG:ASAN>:-fno-omit-frame-pointer>
  $<$<CONFIG:UBSAN>:-fsanitize=undefined>
  $<$<CONFIG:UBSAN>:-fno-omit-frame-pointer>
  $<$<CONFIG:TSAN>:-fsanitize=thread>)

add_link_options(
  -pthread $<$<CONFIG:ASAN>:-fsanitize=address>
  $<$<CONFIG:UBSAN>:-fsanitize=undefined> $<$<CONFIG:TSAN>:-fsanitize=thread>)

# 
# Add `DEBUG` symbol when not in release mode
# 
add_compile_definitions($<$<NOT:$<CONFIG:RELEASE>>:DEBUG>)

# 
# Build Libraries
# 
add_subdirectory(src)

# 
# Build the Executable
# 
add_executable(main apps/main.c)
target_link_libraries(main PUBLIC
    selectionsort_lib
    vec_lib
    llist_lib
    htable_lib
    bst_lib)

# 
# Build Tests
# 
add_subdirectory(tests)
