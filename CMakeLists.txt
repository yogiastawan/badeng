cmake_minimum_required(VERSION 3.0.0...3.27)
project(badeng VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

include_directories(include)

add_library(badeng core/badeng.c)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(tests)