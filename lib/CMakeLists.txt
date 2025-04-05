cmake_minimum_required(VERSION 3.10)

project(lib_test C)


set(LIBRARY_SRC src/funcs.c)

include_directories("include/")

if (BUILD_STATIC)
    message(STATUS "Building static library")
    add_library(funcs STATIC ${LIBRARY_SRC})
else()
    message(STATUS "Building shared library")
    add_library(funcs SHARED ${LIBRARY_SRC})
endif()

add_executable(main src/main.c)

target_link_libraries(main funcs)
