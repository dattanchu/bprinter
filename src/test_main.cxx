#include "tprinter/table_printer.h"

int main(int argc, char** argv){
    tprinter::TablePrinter tp;

    /* Uncomment/comment-out the following lines and see how it effects the table output */

//  tp.alignCenter();
//  tp.setDashedRawsStyle();
//  tp.setPadding(1);
//  tp.dontUseFixedPointsNotation();
//  tp.setFloatingPointPrecision(5);
//  tp.addMergedColumn("This is merged column1");
//  tp.addMergedColumn("This is merged column2");
//  tp.dontUseFixedPointsNotation();

    tp.addColumn("Name", 10);
    tp.addColumn("Age", 6);
    tp.addColumn("Position", 15);
    tp.addColumn("Allowance", 20); //NOTICE how the long words in this column are trimmed

    tp << "Dat Chu" << 25 << "Research Assistant" << -0.00000000001337;
    tp << "John Doe" << 26 << "Too much float" << 125456789.129456789;
    tp << "John Doe" << 26 << "Typical Int" << tprinter::intToHex(66000);
    tp << "John Doe" << 26 << "Typical float" << 1254.3712;
    tp << "John Doe" << 26 << "Too much negative" << -125456789.123456789;
    tp << "John Doe" << 26 << "Exact size int" << 125456789;
    tp << "John Doe" << 26 << "Exact size float" << -1254567.8;
    tp << "John Doe" << 26 << "Negative Int" << -1254;
    tp << "Jane Doe" << tprinter::blank();
    tp << "Tom Doe" << 7 << "Student" << -3.14;

    tp.print();

    return 1;
}
