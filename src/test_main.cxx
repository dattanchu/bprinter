#include "bprinter/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>

#if defined(USE_BOOST_KARMA)
#include <boost/spirit/include/karma.hpp>
namespace karma = boost::spirit::karma;
#endif

using bprinter::TablePrinter;
int main(int argc, char** argv){
    TablePrinter tp;
    tp.alignLeft();
    //tp.setPadding(2);
    tp.addColumn("Name", 25);
    tp.addColumn("Age", 5);
    tp.addColumn("Position", 30);
    tp.addColumn("Allowance", 9);
    tp.addMergedColumn("This is merged column1");
    tp.addMergedColumn("This is merged column2");


    tp << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
    tp << "John Doe" << 26 << "Too much float" << 125456789.123456789;
    tp << "John Doe" << 26 << "Typical Int" << 1254;
    tp << "John Doe" << 26 << "Typical float" << 1254.36;
    tp << "John Doe" << 26 << "Too much negative" << -125456789.123456789;
    tp << "John Doe" << 26 << "Exact size int" << 125456789;
    tp << "John Doe" << 26 << "Exact size int" << -12545678;
    tp << "John Doe" << 26 << "Exact size float" << -1254567.8;
    tp << "John Doe" << 26 << "Negative Int" << -1254;
    tp << "Jane Doe" << bprinter::blank();
    tp << "Tom Doe" << 7 << "Student" << -M_PI;


    tp.print();

    return 1;
}
