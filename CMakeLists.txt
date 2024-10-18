cmake_minimum_required(VERSION 3.10)

project(konata)

set(CMAKE_C_STANDARD 11)

add_library(knt STATIC knt.c)

add_library(knt_utils STATIC knt_utils.c)

install(
    TARGETS knt
    ARCHIVE DESTINATION lib
)

install(
    TARGETS knt_utils
    ARCHIVE DESTINATION lib
)

install(FILES knt.h DESTINATION include)

install(FILES knt_utils.h DESTINATION include)

include(GNUInstallDirs)
