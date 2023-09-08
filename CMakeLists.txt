cmake_minimum_required(VERSION 3.0.0...3.27)
project(badeng VERSION 0.1.0 LANGUAGES C)

include(CTest)
enable_testing()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_definitions(-DGX_DEBUG)
endif ()

include_directories(include)

add_subdirectory(thirdparties/SDL2-2.28.3)
include_directories(thirdparties/SDL2-2.28.3/include)

add_library(badeng SHARED core/badeng.c
        system/entity.c
        system/component.c)
target_link_libraries(
        badeng
        
        SDL2
        GL)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

add_subdirectory(tests)