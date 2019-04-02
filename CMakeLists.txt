cmake_minimum_required(VERSION 3.13)
project(tpritner)

add_definitions(-std=c++98)

include_directories(include)
include_directories(include/tprinter)

add_executable(tpritner
        include/tprinter/table_printer.h
        src/table_printer.cpp
        src/test_main.cxx)
