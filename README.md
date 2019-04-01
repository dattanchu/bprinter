# Usage
Usage is pretty straigh forwared. For commented API see header file.

Here is the simplest usage example:
```cpp
#include "bprinter/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>

using bprinter::TablePrinter;
int main(int argc, char** argv){
    TablePrinter tp;
    tp.alignLeft();
    tp.addColumn("Name", 25);
    tp.addColumn("Age", 6);
    tp.addColumn("Position", 30);
    tp.addColumn("Allowance", 9);

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
```

Output:
```
+-------------------------------------------------------------------------+
|Name                     |Age   |Position                      |Allowance|
+-------------------------------------------------------------------------+
|Dat Chu                  |25    |Research Assistant            |-0.00000*|
|John Doe                 |26    |Too much float                |12545678*|
|John Doe                 |26    |Typical Int                   |1254     |
|John Doe                 |26    |Typical float                 |1254.360*|
|John Doe                 |26    |Too much negative             |-1254567*|
|John Doe                 |26    |Exact size int                |125456789|
|John Doe                 |26    |Exact size int                |-12545678|
|John Doe                 |26    |Exact size float              |-1254567*|
|John Doe                 |26    |Negative Int                  |-1254    |
|Jane Doe                 |      |                              |         |
|Tom Doe                  |7     |Student                       |-3.14159*|
+-------------------------------------------------------------------------+

```

Here is a more advanced usage example:
```cpp
#include "bprinter/table_printer.h"
#define _USE_MATH_DEFINES
#include <math.h>

using bprinter::TablePrinter;
int main(int argc, char** argv){
    TablePrinter tp;
    tp.alignCenter();
    tp.setDashedRawsStyle();
    tp.setPadding(1);
    tp.addColumn("Name", 25);
    tp.addColumn("Age", 6);
    tp.addColumn("Position", 10); 
    tp.addColumn("Allowance", 9); //NOTICE how the long words in this column are trimmed
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
```

Output:
```
+-----------------------------------------------------+
|                This is merged column1               |
+-----------------------------------------------------+
|                This is merged column2               |
+-----------------------------------------------------+
|           Name          |  Age | Position |Allowance|
+-----------------------------------------------------+
+-----------------------------------------------------+
|         Dat Chu         |  25  |Research *|-0.00000*|
+-----------------------------------------------------+
|         John Doe        |  26  |Too much *|12545678*|
+-----------------------------------------------------+
|         John Doe        |  26  |Typical I*|   1254  |
+-----------------------------------------------------+
|         John Doe        |  26  |Typical f*|1254.360*|
+-----------------------------------------------------+
|         John Doe        |  26  |Too much *|-1254567*|
+-----------------------------------------------------+
|         John Doe        |  26  |Exact siz*|125456789|
+-----------------------------------------------------+
|         John Doe        |  26  |Exact siz*|-12545678|
+-----------------------------------------------------+
|         John Doe        |  26  |Exact siz*|-1254567*|
+-----------------------------------------------------+
|         John Doe        |  26  |Negative *|  -1254  |
+-----------------------------------------------------+
|         Jane Doe        |      |          |         |
+-----------------------------------------------------+
|         Tom Doe         |   7  |  Student |-3.14159*|
+-----------------------------------------------------+
```

## Be in touch
Bug fixes, comments and requests are welcomed at https://github.com/dattanchu/bprinter
