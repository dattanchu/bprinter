#include "bprinter/table_printer.h"
using bprinter::TablePrinter;
int main(int argc, char** argv){
  TablePrinter tp(&std::cout);
  tp.AddColumn("Name", 25);
  tp.AddColumn("Age", 3);
  tp.AddColumn("Position", 30);

  tp.PrintHeader();
  tp << "Dat Chu" << 25 << "Research Assistant";
  tp << "John Doe" << 26 << "Professional Anonymity";
  tp << "Jane Doe" << bprinter::endl();
  tp << "Tom Doe" << 7 << "Student";
  tp.PrintFooter();
  return 1;
}
