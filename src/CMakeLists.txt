add_library(vec_lib vec.c)
target_include_directories(vec_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(vec_lib PRIVATE some_other_lib)

add_library(llist_lib llist.c)
target_include_directories(llist_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(llist_lib PRIVATE some_other_lib)

add_library(htable_lib htable.c)
target_include_directories(htable_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(htable_lib PRIVATE some_other_lib)

add_library(bst_lib bst.c)
target_include_directories(bst_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
# target_link_libraries(bst_lib PRIVATE some_other_lib)
