#ifndef BPRINTER_TABLE_PRINTER_H_
#define BPRINTER_TABLE_PRINTER_H_

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

namespace bprinter {

    class blank{};

    class TablePrinter {

    public:

        TablePrinter();
        TablePrinter(const std::string & separator);

        int getNumColumns() const { return column_headers_.size(); }

        int getTableWidth() const { return table_width_; }

        /// \brief Set columns seperator
        void setSeperator(const std::string &separator) { separator_ = separator; }

        /** \brief Add a column with header to the table
        **
        ** \param header_name Name to be print for the header
        ** \param column_width the width of the column
        ** */
        void addColumn(const std::string &header_name, int column_width);

        /** \brief Add a merged column with header to the table.
        **  Merged column is a title column with the same width as
         *  the whole table width. It is usually useful for printing
         *  the table name
        ** \param header_name Name to be print for the header
        ** \param column_width the width of the column
        ** */
        void addMergedColumn(const std::string &header_name);

        /// \brief Align the text in the table to the left
        void alignLeft() { alignment_ = LEFT; }

        /// \brief Align the text in the table to the right
        void alignRight() { alignment_ = RIGHT; }

        /// \brief Align the text in the table to the center
        void alignCenter() { alignment_ = CENTER; }

        /** \brief Set padding around text where there is enough room
        ** \param padding How much white spaces pad with on each side
         * of the text
        ** */
        void setPadding(int padding) { padding_ = padding; }

        /** \brief Print dashed line after each table row to seperate
         *  between rows
         */
        void setDashedRawsStyle() { style_ = DASHED; };

        /** \brief Print lines one after another without separating
         *  dashed lines
         */
        void setStandartStyle() { style_ = STANDARD; };

        /** \brief Print the table. Set table text and settings before
        *   calling this function
        */
        void print();

        /** \brief Get the table output as string. Set table text and settings before
         *  calling this function
         *  \return string output of the table
        */
        std::string getTableOutput() { return generateTable(); }

        TablePrinter& operator<<(blank input);
        TablePrinter& operator<<(float input);
        TablePrinter& operator<<(double input);
        template<typename T> TablePrinter& operator<<(T input){
            addAlignmentToStream(data_stream_);
            if (current_column_index_ == 0) {
                data_stream_  << "|";
            }
            const int column_width = column_widths_.at(current_column_index_);
            const std::string input_str = TablePrinter::typeToString(input);
            const std::string bounded_str = boundString(input_str, column_width);
            const std::string padded_str = padBoundedString(bounded_str, column_width, padding_);
            data_stream_  << std::setw(column_width);
            if (alignment_ == CENTER) {
                data_stream_  << alignBoundedStringToCenter(padded_str, column_width);
            } else {
                data_stream_  << padded_str;
            }
            if (current_column_index_ == getNumColumns()-1){
                data_stream_  << "|\n";
                if (style_ == DASHED) {
                    addHorizontalLineToStream(data_stream_);
                }
                current_row_index_ = current_row_index_ + 1;
                current_column_index_ = 0;
            } else {
                data_stream_  << separator_;
                current_column_index_ = current_column_index_ + 1;
            }
            return *this;
        }

    private:

        enum Alignment {
            LEFT = 0,
            RIGHT,
            CENTER
        };

        enum Style {
            STANDARD = 0,
            DASHED
        };

        void initialize(const std::string & separator);
        void addHeaderToStream(std::stringstream & stream);

        template<typename T> static std::string typeToString(T input) {
            std::ostringstream stream;
            stream << std::dec << input;
            return stream.str();
        }

        std::string generateTable();

        /// \brief align string to center within the limits of bounded width
        std::string alignBoundedStringToCenter(const std::string &str, int width);

        /// \brief pad string within the limits of bounded width
        std::string padBoundedString(const std::string &str, int width, int padding);

        /// \brief enforce width limits on a string
        std::string boundString(const std::string &str, int width);

        /// \brief add dashed line (raw separator) to stream
        void addHorizontalLineToStream(std::stringstream & stream);

        /// \brief apply chosen alignment direction to stream
        void addAlignmentToStream(std::stringstream & stream);

        /// \brief enforce width limits on a decimal point number (float or double)
        template<typename T> std::string boundDecimalNumber(T input) {
            std::stringstream result_str;
            addAlignmentToStream(result_str);
            const int column_width = column_widths_.at(current_column_index_);
            if (input < 10 * (column_width-1) || input > 10 * column_width){
                std::stringstream string_out;
                string_out << std::setiosflags(std::ios::fixed)
                           << std::setprecision(column_width)
                           << std::setw(column_width)
                           << input;
                std::string string_rep_of_number = string_out.str();
                string_rep_of_number[column_width - 1] = '*';
                std::string string_to_print = string_rep_of_number.substr(0, column_width);
                result_str << string_to_print;
            } else {
                // determine what precision we need
                int precision = column_width - 1; // leave room for the decimal point
                if (input < 0) {
                    --precision; // leave room for the minus sign
                }
                // leave room for digits before the decimal
                if (input < -1 || input > 1){
                    int num_digits_before_decimal = 1 + (int)log10(std::abs(input));
                    precision -= num_digits_before_decimal;
                } else {
                    precision--; // e.g. 0.12345 or -0.1234
                }
                if (precision < 0) {
                    precision = 0; // don't go negative with precision
                }
                result_str  << std::setiosflags(std::ios::fixed)
                             << std::setprecision(precision)
                             << std::setw(column_width)
                             << input;
            }
            if (current_column_index_ == getNumColumns()-1){
                result_str  << "|\n";
                if (style_ == DASHED) {
                    addHorizontalLineToStream(result_str);
                }
                current_row_index_ = current_row_index_ + 1;
                current_column_index_ = 0;
            } else {
                result_str  << separator_;
                current_column_index_ = current_column_index_ + 1;
            }

            return result_str.str();
        }

        std::vector<std::string> column_headers_;
        std::vector<std::string> merged_column_headers_;
        std::vector<int> column_widths_;
        std::string separator_;
        std::stringstream data_stream_;

        int current_row_index_;
        int current_column_index_;

        int table_width_;
        int padding_;
        Alignment alignment_;
        Style style_;
    };

}

#endif
