project(tests_eng C CXX)

include(CTest)
enable_testing()

# add test 1
add_executable(test1 test1.c)
find_library(badeng badeng)
target_link_libraries(test1 badeng)
add_test(Test1 test1)