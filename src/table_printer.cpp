#include "bprinter/table_printer.h"
#include <stdexcept>
#include <iomanip>
#include <stdexcept>

namespace bprinter {

    TablePrinter::TablePrinter() {
        initialize("|");
    }

    TablePrinter::TablePrinter(const std::string & separator){
        initialize(separator);
    }

    void TablePrinter::initialize(const std::string & separator) {
        column_headers_.reserve(5);
        merged_column_headers_.reserve(2);
        alignLeft();
        setStandartStyle();
        separator_ = separator;
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

    std::string TablePrinter::boundString(const std::string &str, int width) {
        if (width >= str.length()){
            return str;
        }
        int space_to_cut = str.length() - width;
        std::string bounded_str = str.substr(0, str.length()-space_to_cut-1); //cut space, and leave place for astrix
        bounded_str += "*";
        return bounded_str;
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
        if (header_name.length() < 1) {
            return;
        }
        if (column_width < header_name.length()){
            column_width = header_name.length();
        }
        column_headers_.push_back(header_name);
        column_widths_.push_back(column_width);
        table_width_ += column_width + separator_.size();
    }

    void TablePrinter::addMergedColumn(const std::string &header_name) {
        merged_column_headers_.push_back(header_name);
    }

    void TablePrinter::addHorizontalLineToStream(std::stringstream & stream) {
        stream << "+"; // the left bar
        for (int i = 0; i < (table_width_ - 1); ++i) {
            stream << "-";
        }
        stream << "+" << std::endl; // the right bar
    }

    void TablePrinter::addAlignmentToStream(std::stringstream & stream) {
        if(alignment_ == LEFT) {
            stream << std::left;
        } else if (alignment_ == RIGHT) {
            stream << std::right;
        }
    }

    void TablePrinter::addHeaderToStream(std::stringstream & stream){
        addAlignmentToStream(stream);
        addHorizontalLineToStream(stream);


        // add merged headers
        for (int header_idx = 0; header_idx < merged_column_headers_.size(); ++header_idx) {
            stream << "|";
            const std::string header = merged_column_headers_.at(header_idx);
            const int column_width = table_width_-1;
            const std::string padded_header = padBoundedString(header, column_width, padding_);
            stream << std::setw(column_width);
            stream << alignBoundedStringToCenter(padded_header, column_width);
            stream << "|\n";
            addHorizontalLineToStream(stream);
        }

        stream << "|";
        // add columns header
        for (int column = 0; column < getNumColumns(); ++column) {
            const int column_width = column_widths_.at(column);
            const std::string column_header = column_headers_.at(column);
            const std::string padded_header = padBoundedString(column_header, column_width, padding_);
            stream << std::setw(column_width);
            if (alignment_ == CENTER) {
                stream << alignBoundedStringToCenter(padded_header, column_width);
            } else {
                stream << padded_header;
            }
            if (column != getNumColumns()-1) {
                stream << separator_;
            }
        }
        stream << "|\n";
        addHorizontalLineToStream(stream);
        if (style_ == DASHED) {
            addHorizontalLineToStream(stream);
        }
    }

    std::string TablePrinter::generateTable() {
        if (column_headers_.size() < 1) {
            return "";
        }
        std::stringstream stream;

        //build header
        addHeaderToStream(stream);
        // build body
        stream << data_stream_.str();
        // build footer
        if (style_ != DASHED) {
            addHorizontalLineToStream(stream);
        }
        return stream.str();
    }

    void TablePrinter::print() {
        printf("%s", generateTable().c_str());
    }

    TablePrinter& TablePrinter::operator<<(blank input){
        while (current_column_index_ != 0){
            *this << "";
        }
        return *this;
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
