#ifndef BPRINTER_TABLE_PRINTER_H_
#define BPRINTER_TABLE_PRINTER_H_

#include <iomanip>
#include <vector>
#include <string>
#include <sstream>
#include <cmath>

namespace tprinter {

    class blank{};

    /** \brief Convert integral value to hex representation
    ** \param value: Integral values
     * \return Hex string representation of the integral
    ** */
    template<typename integral_t>
    static std::string intToHex(integral_t value)
    {
        std::stringstream stream;
        stream << std::showbase << std::hex << value;
        return stream.str();
    }

    class TablePrinter {

    public:

        TablePrinter();
        TablePrinter(const std::string & separator);

        int getNumColumns() const { return column_headers_.size(); }

        int getTableWidth() const { return table_width_; }

        /// \brief Set the number of digits to print after decimal point
        void setFloatingPointPrecision(int precision) { floating_point_precision_ = precision; }

        /** \brief Sets the floatfield format flag for the str stream to fixed.
         *  e.g. 125456789.12346 will be presented as 125456789.12346
         */
        void useFixedPointsNotation() { fixed_points_notation_ = true;}

        /** \brief Sets the floatfield format flag for the str stream to fixed.
         *  e.g. 125456789.12346 will be presented as 1.2546e+08
         */
        void dontUseFixedPointsNotation() { fixed_points_notation_ = false;}

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
        void setDashedRawsStyle() { style_ = DASHED_ROWS_SEPARATION; };

        /** \brief Print lines one after another without separating
         *  dashed lines
         */
        void setStandartStyle() { style_ = NO_ROWS_SEPARATION; };

        /** \brief Print the table. Set table text and settings before
        *   calling this function
        */
        void print();

        /** \brief Get the table output as string. Set table text and settings before
         *  calling this function
         *  \return string output of the table
        */
        std::string getTableOutput() { return generateTable(); }

        void reset();

        TablePrinter& operator<<(blank input);
        TablePrinter& operator<<(float input);
        TablePrinter& operator<<(double input);

        template<typename T> TablePrinter& operator<<(T input) {
            addAlignmentToStream(data_stream_);
            if (current_column_index_ == 0) {
                data_stream_  << "|";
            }
            const int column_width = column_widths_.at(current_column_index_);
            const std::string input_str = TablePrinter::typeToString(input);
            const std::string bounded_str = boundString(input_str, column_width);
            const std::string padded_str = padBoundedString(bounded_str, column_width, padding_);
            data_stream_  << std::setw(column_width) << std::fixed << std::setprecision(7);
            if (alignment_ == CENTER) {
                data_stream_  << alignBoundedStringToCenter(padded_str, column_width);
            } else {
                data_stream_  << padded_str;
            }
            if (current_column_index_ == getNumColumns()-1){
                data_stream_  << "|\n";
                if (style_ == DASHED_ROWS_SEPARATION) {
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
            NO_ROWS_SEPARATION = 0,
            DASHED_ROWS_SEPARATION
        };

        void initialize(const std::string & separator);
        void addHeaderToStream(std::stringstream & stream);

        template<typename T> static std::string typeToString(T input) {
            std::ostringstream stream;
            stream << std::dec << input;
            return stream.str();
        }

        template <typename floating_point_t>
        void addFloatingPointToStream(floating_point_t input) {
            std::stringstream float_stream;
            if (fixed_points_notation_) {
                float_stream << std::fixed;
            }
            float_stream << std::setprecision(floating_point_precision_) << input;
            this->operator<<(float_stream.str());
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

        std::vector<std::string> column_headers_;
        std::vector<std::string> merged_column_headers_;
        std::vector<int> column_widths_;
        std::string separator_;
        std::stringstream data_stream_;

        int current_row_index_;
        int current_column_index_;
        int table_width_;
        int padding_;
        int floating_point_precision_;
        bool fixed_points_notation_;
        Alignment alignment_;
        Style style_;
    };

}

#endif
