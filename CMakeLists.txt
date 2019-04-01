cmake_minimum_required(VERSION 3.13)
project(bprinter)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)
include_directories(include/bprinter)

add_executable(bprinter
        .idea/bprinter.iml
        .idea/encodings.xml
        .idea/misc.xml
        .idea/modules.xml
        .idea/vcs.xml
        .idea/workspace.xml
        cmake-build-debug/bprinter.cbp
        cmake-build-debug/cmake_install.cmake
        cmake-build-debug/CMakeCache.txt
        cmake-build-debug/Makefile
        include/bprinter/table_printer.h
        src/table_printer.cpp
        src/test_main.cxx
        CMakeLists.txt
        config.cmake.in
        LICENSE
        README)
