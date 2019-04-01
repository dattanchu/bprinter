#include "bprinter/table_printer.h"
#include <stdexcept>
#include <iomanip>
#include <stdexcept>

namespace bprinter {

    TablePrinter::TablePrinter() {
        initialize(&std::cout, "|");
    }

    TablePrinter::TablePrinter(std::ostream * output, const std::string & separator){
        initialize(output, separator);
    }

    void TablePrinter::initialize(std::ostream * output, const std::string & separator) {
        out_stream_ = output;
        separator_ = separator;
        alignLeft();
        table_width_ = 0;
        padding_ = 0;
        current_row_index_ = 0;
        current_column_index_ = 0;
    }

    std::string TablePrinter::padBoundedString(const std::string &str, int width, int padding) {
        if (width <= str.length()){
            return str;
        }
        int available_space = width - str.length();
        if (available_space >= padding*2) {
            return std::string(padding, ' ') + str + std::string(padding, ' ');
        }
        return std::string((available_space+1)/2, ' ') + str + std::string(available_space/2, ' ');
    }

    std::string TablePrinter::alignBoundedStringToCenter(const std::string &str, int width) {
        if (width <= str.length()) {
            return str;
        }
        int white_spaces = width - str.length();
        int left_padding = (white_spaces + 1) / 2;
        int right_padding = white_spaces - left_padding;
        return std::string(left_padding, ' ') + str + std::string(right_padding, ' ');
    }

    /** \brief Add a column to our table
     **
     ** \param header_name Name to be print for the header
     ** \param column_width the width of the column (has to be >=5)
     ** */
    void TablePrinter::addColumn(const std::string &header_name, int column_width){
        if (column_width < 4){
            throw std::invalid_argument("Column size has to be >= 4");
        }
        column_headers_.push_back(header_name);
        column_widths_.push_back(column_width);
        table_width_ += column_width + separator_.size();
    }

    void TablePrinter::printHorizontalLine() {
        *out_stream_ << "+"; // the left bar
        for (int i=0; i < table_width_-1; ++i) {
            *out_stream_ << "-";
        }
        *out_stream_ << "+" << std::endl; // the right bar
    }

    void TablePrinter::printHeader(){
        printHorizontalLine();
        *out_stream_ << "|";
        if(alignment_ == LEFT) {
            *out_stream_ << std::left;
        } else if (alignment_ == RIGHT) {
            *out_stream_ << std::right;
        }
        for (int column = 0; column < getNumColumns(); ++column) {
            const int column_width = column_widths_.at(column);
            const std::string column_header = column_headers_.at(column);
            const std::string padded_header = padBoundedString(column_header, column_width, padding_);
            *out_stream_ << std::setw(column_width);
            if (alignment_ == CENTER) {
                *out_stream_ << alignBoundedStringToCenter(padded_header, column_width);
            } else {
                *out_stream_ << padded_header;
            }
            if (column != getNumColumns()-1) {
                *out_stream_ << separator_;
            }
        }
        *out_stream_ << "|\n";
        printHorizontalLine();
    }

    TablePrinter& TablePrinter::operator<<(blank input){
        while (current_column_index_ != 0){
            *this << "";
        }
        return *this;
    }

    void TablePrinter::printFooter(){
        printHorizontalLine();
    }

    TablePrinter& TablePrinter::operator<<(float input){
        printBoundedDecimal<float>(input);
        return *this;
    }

    TablePrinter& TablePrinter::operator<<(double input){
        printBoundedDecimal<double>(input);
        return *this;
    }


}
