project(bprinter)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(bprinterTest src/test_main.cxx)
add_library(bprinter STATIC
  include/bprinter/table_printer.h
  src/table_printer.cpp
)
target_link_libraries(bprinterTest bprinter)
