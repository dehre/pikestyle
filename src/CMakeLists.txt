add_library(selectionsort_lib selectionsort.c)
target_include_directories(selectionsort_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(quicksort_lib quicksort.c quicksort_easy.c)
target_include_directories(quicksort_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(binarysearch_lib binarysearch.c)
target_include_directories(binarysearch_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(vec_lib vec.c)
target_include_directories(vec_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(vec_lib PRIVATE quicksort_lib binarysearch_lib)

add_library(llist_lib llist.c)
target_include_directories(llist_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(htable_lib htable.c)
target_include_directories(htable_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_library(bst_lib bst.c)
target_include_directories(bst_lib PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(bst_lib PRIVATE vec_lib)
